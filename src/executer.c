#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

char		**get_paths(void)
{
	char	*path;
	char	**res;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	res = ft_split(path, ':');
	return (res);
}

char	*search_binary(t_options *o, char *cmd)
{
	char	*absolute_path;
	int		i;

	if (access(cmd, F_OK) >= 0)
		return (ft_strdup(cmd));
	i = 0;
	while (o->paths[i])
	{
		absolute_path = ft_strjoin(o->paths[i], "/");
		absolute_path = ft_strjoin_gnl(absolute_path, cmd);
		if (access(absolute_path, F_OK) >= 0)
			return (absolute_path);
		free(absolute_path);
		i++;
	}
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	panic(o, EXIT_FAILURE);
	return (NULL);
}

static char	**build_args(t_parse_cmd *cmd)
{
	char	**args;
	int		i;
	int		l;

	l = 0;
	while (cmd->args[l])
		l++;
	args = ft_calloc(sizeof(char *), l + 2);
	i = 0;
	args[0] = ft_strdup(cmd->cmd);
	l = -1;
	while (cmd->args[++l])
		args[++i] = ft_strdup(cmd->args[l]);
	return (args);
}

static void	execute_pipe(t_options *o, t_parse_table *cmd, t_parse_table *next_cmd)
{
	char	*binary;
	char	**args;
	int		child;
	int		fd[2];

	if (pipe(fd) == -1)
		panic(o, 1);
	child = fork();
	if (child < 0)
		panic(o, 1);
	if (child == 0)
	{
		next_cmd->in = fd[0];
		close(next_cmd->in);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	close(fd[1]);
	close(next_cmd->in);
}

int	try_buildin(t_options *o, t_parse_table *cmd)
{
	if (ft_strncmp(cmd->cmd->cmd, "cd", 2) == 0)
		return (ft_cd(o, cmd), 1);
	if (ft_strncmp(cmd->cmd->cmd, "echo", 4) == 0)
		return (ft_echo(o, cmd), 1);
	if (ft_strncmp(cmd->cmd->cmd, "pwd", 3) == 0)
		return (ft_pwd(o), 1);
	if (ft_strncmp(cmd->cmd->cmd, "export", 6) == 0)
		return (ft_export(o, cmd), 1);
	if (ft_strncmp(cmd->cmd->cmd, "unset", 5) == 0)
		return (ft_unset(o, cmd), 1);
	if (ft_strncmp(cmd->cmd->cmd, "env", 3) == 0)
		return (ft_env(o), 1);
	if (ft_strncmp(cmd->cmd->cmd, "exit", 4) == 0)
		return (panic(o, 0), 1);
	return (0);
}

static int execute_non_pipe(t_options *o, t_parse_table *cmd)
{
	char	*binary;
	char	**args;
	int		child;

	if (try_buildin(o, cmd))
		return (-1);
	child = fork();
	if (child < 0)
		panic(o, 1);
	if (child == 0)
	{
		binary = search_binary(o, cmd->cmd->cmd);
		args = build_args(cmd->cmd);
		execve(binary, args, o->env);
		free(binary);
		split_free(args);
		return (0);
	}
	return (0);
}


char	*read_fd(int fd)
{
	char	*tmp;
	char	*content;
	char	*line;

	line = get_next_line(fd);
	content = ft_strdup("");
	while (line)
	{
		tmp = ft_strjoin(content, line);
		free(content);
		content = ft_strdup(tmp);
		free(tmp);
		free(line);
		line = get_next_line(fd);
	}
	return (content);
}

void	executer(t_options *o)
{
	int	    i;
	int	    l;
	int		pid;

	l = 0;
	while (o->tables[l])
		l++;
	i = -1;
	while (o->tables[++i])
	{
		if (o->tables[i]->out == -2)
			execute_pipe(o, o->tables[i], o->tables[i + 1]);
		else
			pid = execute_non_pipe(o, o->tables[i]);
		if (pid == 0)
			waitpid(0, NULL, 0);
	}
}
