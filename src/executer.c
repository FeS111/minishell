#include "../include/minishell.h"
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

static char	**build_args(char **cmd)
{
	char	**args;

	args = ft_calloc(sizeof(char *), 5);
	args[0] = cmd[CMD];
	args[1] = cmd[OPT];
	args[2] = cmd[OPT2];
	args[3] = cmd[ARGS];
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

static void execute_non_pipe(t_options *o, t_parse_table *cmd)
{
	char	*binary;
	char	**args;
	int		child;

	child = fork();
	if (child < 0)
		panic(o, 1);
	if (child == 0)
	{
		binary = search_binary(o, cmd->cmd[CMD]);
		args = build_args(cmd->cmd);
		execve(binary, args, o->env);
		free(binary);
		split_free(args);
	}
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

	l = 0;
	while (o->tables[l])
		l++;
	i = -1;
	while (o->tables[++i])
	{
		if (o->tables[i]->out == -2)
			execute_pipe(o, o->tables[i], o->tables[i + 1]);
		else
			execute_non_pipe(o, o->tables[i]);
		waitpid(0, NULL, 0);
	}
}
