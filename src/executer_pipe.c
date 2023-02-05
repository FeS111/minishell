#include "../include/executer.h"

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

int	run_pipe(t_options *o, int *i, int *fd, pid_t *last_child)
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

void	execute_pipe(t_options *o, int *i, int *fd)
{
	pid_t last_child;
	int	pipe;

	pipe = o->pipes;
	while (o->tables[*i] && o->pipes >= 0)
	{
		if (!ft_strncmp(o->tables[*i]->cmd->cmd, "here_doc", 9))
			*i += 1;
		fd[0] = run_pipe(o, i, fd, &last_child);
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
