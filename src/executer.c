#include "../include/minishell.h"
#include <signal.h>
#include <sys/wait.h>

int	g_in_executer;

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

	if (cmd[0] == '/' && access(cmd, X_OK) >= 0)
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
	while (cmd->args && cmd->args[l])
		l++;
	args = ft_calloc(sizeof(char *), l + 2);
	i = 0;
	args[0] = ft_strdup(cmd->cmd);
	l = -1;
	while (cmd->args && cmd->args[++l])
		args[++i] = ft_strdup(cmd->args[l]);
	return (args);
}

static void	do_op(t_options *o, t_parse_cmd *cmd)
{
	char	*binary;
	char	**args;

	if (try_builtin(o, cmd))
		 panic(o, EXIT_SUCCESS);
	binary = search_binary(o, cmd->cmd);
	args = build_args(cmd);
	execve(binary, args, o->env);
	free(binary);
	split_free(args);
	exit(EXIT_FAILURE);
}

void	execute_child(t_options *o, t_parse_cmd *cmd, int *fd, int *pipefd)
{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		close(pipefd[0]);
		if (o->pipes > 0)
			dup2(pipefd[1], STDOUT_FILENO);
		if (o->pipes == 0 && fd[1] != STDOUT_FILENO)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		close(pipefd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		do_op(o, cmd);
}

static int	run(t_options *o, int *i, int *fd, pid_t *last_child)
{
	int		pipefd[2];
	pid_t	child;

	if (pipe(pipefd) == -1)
		panic(o, 1);
	child = fork();
	if (child < 0)
		panic(o, 1);
	else if (child == 0)
		execute_child(o, o->tables[*i]->cmd, fd, pipefd);
	o->pipes--;
	if (o->pipes < 0)
		*last_child = child;
	close(fd[0]);
	close(pipefd[1]);
	if (fd[1] != STDOUT_FILENO)
		close(fd[1]);
	return (pipefd[0]);
}


static void	execute_pipe(t_options *o, int *i, int *fd)
{
	pid_t last_child;
	int	pipe;

	pipe = o->pipes;
	while (o->tables[*i] && o->pipes >= 0)
	{
		fd[0] = run(o, i, fd, &last_child);
		*i += 1;
	}
	waitpid(last_child, &o->last_status, 0);
	while (pipe) 
	{
		pipe--;
		wait(NULL);
	}
	close(fd[0]);
	if (fd[1] != STDOUT_FILENO)
		close(fd[1]);
}

int	try_builtin(t_options *o, t_parse_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "cd\0", 3) == 0)
		return (ft_cd(o, cmd), 1);
	if (ft_strncmp(cmd->cmd, "echo\0", 5) == 0)
		return (ft_echo(o, cmd), 1);
	if (ft_strncmp(cmd->cmd, "pwd\0", 4) == 0)
		return (ft_pwd(o), 1);
	if (ft_strncmp(cmd->cmd, "export\0", 7) == 0)
		return (ft_export(o, cmd), 1);
	if (ft_strncmp(cmd->cmd, "unset\0", 6) == 0)
		return (ft_unset(o, cmd), 1);
	if (ft_strncmp(cmd->cmd, "env\0", 4) == 0)
		return (ft_env(o), 1);
	if (ft_strncmp(cmd->cmd, "exit\0", 5) == 0)
		return (panic(o, 0), 1);
	return (0);
}

static int execute_non_pipe(t_options *o, t_parse_table *cmd, int *fd)
{
	int		child;

	if (try_builtin(o, cmd->cmd))
		return (-1);
	child = fork();
	if (child < 0)
		panic(o, 1);
	if (child == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (fd[1] != STDOUT_FILENO)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		do_op(o, cmd->cmd);
	}
	if (fd[0] != STDOUT_FILENO)
		close(fd[0]);
	close(fd[0]);
	return (child);
}

char	*read_fd(int in)
{
	char	*tmp;
	char	*content;
	char	*line;

	line = get_next_line(in);
	content = ft_strdup("");
	while (line)
	{
		tmp = ft_strjoin(content, line);
		free(content);
		content = ft_strdup(tmp);
		free(tmp);
		free(line);
		line = get_next_line(in);
	}
	return (content);
}

int	get_in(t_parse_table **tables)
{
	int	i;

	i = 0;
	while (tables[i])
		i++;
	i -= 1;
	while (i >= 0)
	{
		if (tables[i]->in == READ)
		{
			if (!ft_strncmp(tables[i]->cmd->cmd, "here_doc", 9))
				return (open("here_doc", O_RDONLY));
			else
				return (open(tables[i]->cmd->cmd, O_RDONLY));
		}
		i--;
	}
	return (dup(STDIN_FILENO));
}

int	get_out(t_parse_table **tables)
{
	int	i;

	i = 0;
	while (tables[i])
		i++;
	i -= 1;
	while (i >= 0)
	{
		if (tables[i]->out == WRITE)
		{
			if (tables[i]->cmd->args 
					&& !ft_strncmp(tables[i]->cmd->args[0], ">>", 2))
				return (open(tables[i]->cmd->cmd, 
							O_APPEND | O_WRONLY, 0644));
			return (open(tables[i]->cmd->cmd,
						O_CREAT | O_TRUNC | O_WRONLY, 0644));
		}
		i--;
	}
	return (STDOUT_FILENO);
}

void	executer(t_options *o)
{
	int	    i;
	pid_t	pid;
	int		fd[2];

	i = 0;
	fd[0] = get_in(o->tables);
	fd[1] = get_out(o->tables);
	if (fd[1] == -1)
	{
		perror(o->tables[i]->cmd->cmd);
		close(fd[0]);
		o->last_status = 1;
		return ; 
	}
	g_in_executer = 1;
	if (o->tables[i])
	{
		if (o->pipes > 0 && o->tables[i]->out != WRITE && ft_strncmp(o->tables[i]->cmd->cmd, "here_doc", 9))
			execute_pipe(o, &i, fd);
		else if (o->tables[i]->out != WRITE && ft_strncmp(o->tables[i]->cmd->cmd, "here_doc", 9))
		{
			pid = execute_non_pipe(o, o->tables[i], fd);
			waitpid(pid, &o->last_status, 0);
		}
		close(fd[0]);
		if (fd[1] != STDOUT_FILENO)
			close(fd[1]);
	}	
}
