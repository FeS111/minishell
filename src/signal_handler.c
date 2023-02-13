/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:56:22 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/07 14:01:09 by fschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global g_global;

void	ctrl_c_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		if (!g_global.in_executer)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	set_status(pid_t last_child)
{
	int	status;

	waitpid(last_child, &status, 0);
	if (WIFSIGNALED(status))
	{
		g_global.status = WTERMSIG(status);
		if (g_global.status == 2)
			g_global.status = 130;
		else
			g_global.status = 131;
	}
	else
		g_global.status = WEXITSTATUS(status);
}
