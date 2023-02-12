/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:55:40 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/12 13:27:41 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	fork_builtin(t_options *o, t_parse_cmd *cmd)
{
	if (!cmd->cmd)
		return (0);
	if (ft_strncmp(cmd->cmd, "echo\0", 5) == 0)
		return (ft_echo(o, cmd), 1);
	if (ft_strncmp(cmd->cmd, "pwd\0", 4) == 0)
		return (ft_pwd(o), 1);
	if (ft_strncmp(cmd->cmd, "env\0", 4) == 0)
		return (ft_env(o), 1);
	if (ft_strncmp(cmd->cmd, "cd\0", 3) == 0)
		return (1);
	if (ft_strncmp(cmd->cmd, "export\0", 7) == 0)
		return (1);
	if (ft_strncmp(cmd->cmd, "unset\0", 6) == 0)
		return (1);
	if (ft_strncmp(cmd->cmd, "exit\0", 5) == 0)
		return (ft_exit(o, cmd), 1);
	return (0);
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

int	run_pipe(t_options *o, int *i, int *fd, pid_t *last_child)
{
	int		pipefd[2];
	pid_t	child;

	// if (o->tables[*i]->in != PIPE)
	// {
	// 	close(fd[0]);
	// 	fd[0] = get_in(o->tables[*i]);
	// }
	// fd[1] = get_out(o->tables[*i]);
	ft_putnbr_fd(fd[0], 2);
	ft_putchar_fd('\n', 2);
	ft_putnbr_fd(fd[1], 2);
	ft_putchar_fd('\n', 2);
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
	return (pipefd[0]);
}

void	execute_pipe(t_options *o, int *i, int *fd)
{
	pid_t	last_child;
	int		pipe;

	pipe = o->pipes;
	while (o->tables[*i] && o->pipes >= 0)
	{
		fd[0] = run_pipe(o, i, fd, &last_child);
		*i += 1;
	}
	waitpid(last_child, &o->last_status, 0);
	o->last_status = WEXITSTATUS(o->last_status);
	while (pipe)
	{
		pipe--;
		wait(NULL);
	}
	close(fd[0]);
	if (fd[1] != STDOUT_FILENO)
		close(fd[1]);
}
