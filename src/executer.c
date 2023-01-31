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

static void	do_op(t_options *o, t_parse_cmd *cmd)
{
	char	*binary;
	char	**args;

	binary = search_binary(o, cmd->cmd);
	args = build_args(cmd);
	execve(binary, args, o->env);
	free(binary);
	split_free(args);
	ft_putendl_fd("error", 2);
}

static int	run(t_options *o, int *pipefd, int fd, int *i)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		panic(o, 1);
	else if (child == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		dup2(fd, STDIN_FILENO);
		close(fd);
		do_op(o, o->tables[*i]->cmd);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}


static void	execute_pipe(t_options *o, t_parse_table **tables, int *i)
{
	int		fd;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		panic(o, 1);
	fd = pipefd[0];
	while (tables[*i])
	{
		fd = run(o, pipefd, fd, i);
		*i += 1;
		waitpid(0, NULL, 0);
	}
	close(fd);
	close(pipefd[0]);
	close(pipefd[1]);
}

int	try_buildin(t_options *o, t_parse_table *cmd)
{
	if (ft_strncmp(cmd->cmd->cmd, "cd\0", 3) == 0)
		return (ft_cd(o, cmd), 1);
	if (ft_strncmp(cmd->cmd->cmd, "echo\0", 5) == 0)
		return (ft_echo(o, cmd), 1);
	if (ft_strncmp(cmd->cmd->cmd, "pwd\0", 4) == 0)
		return (ft_pwd(o), 1);
	if (ft_strncmp(cmd->cmd->cmd, "export\0", 7) == 0)
		return (ft_export(o, cmd), 1);
	if (ft_strncmp(cmd->cmd->cmd, "unset\0", 6) == 0)
		return (ft_unset(o, cmd), 1);
	if (ft_strncmp(cmd->cmd->cmd, "env\0", 4) == 0)
		return (ft_env(o), 1);
	if (ft_strncmp(cmd->cmd->cmd, "exit\0", 5) == 0)
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
	binary = search_binary(o, cmd->cmd->cmd);
	if (!binary)
		return (-1);
	child = fork();
	if (child < 0)
		panic(o, 1);
	if (child == 0)
	{
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
		if (o->tables[i]->out == PIPE_FD)
			execute_pipe(o, o->tables, &i);
		else
			pid = execute_non_pipe(o, o->tables[i]);
		if (pid == 0)
			waitpid(0, NULL, 0);
	}
}
