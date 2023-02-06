#include "../include/executer.h"

int	g_in_executer;

void	do_op(t_options *o, t_parse_cmd *cmd)
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
	exit(127);
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
		return (ft_exit(o, cmd), 1);
	return (0);
}

static int	execute_non_pipe(t_options *o, t_parse_table *cmd, int *fd)
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

void	execute_cmd(t_options *o, int i, int *fd)
{
	pid_t	pid;

	if (o->pipes > 0 && o->tables[i]->out != WRITE && o->tables[i]->in != READ
		&& ft_strncmp(o->tables[i]->cmd->cmd, "here_doc", 9))
		execute_pipe(o, &i, fd);
	else if (o->tables[i]->out != WRITE && o->tables[i]->in != READ
			&& ft_strncmp(o->tables[i]->cmd->cmd, "here_doc", 9))
	{
		pid = execute_non_pipe(o, o->tables[i], fd);
		waitpid(pid, &o->last_status, 0);
		o->last_status = WEXITSTATUS(o->last_status);
	}
	close_fd(fd);
}

void	executer(t_options *o)
{
	int		i;
	int		fd[2];

	i = 0;
	fd[0] = get_in(o->tables);
	fd[1] = get_out(o->tables);
	if (fd[1] == -1)
	{
		perror(o->tables[i]->cmd->cmd);
		close_fd(fd);
		o->last_status = 1;
		return ;
	}
	g_in_executer = 1;
	if (o->tables[i])
	{
		if(o->tables[i]->in == READ && o->tables[i + 1])
			i++;
		execute_cmd(o, i, fd);
		i++;
	}
}
