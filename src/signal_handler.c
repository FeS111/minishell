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

int	g_in_executer;

void	ctrl_c_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		if (!g_in_executer)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	set_status(t_options *o, pid_t last_child)
{
	waitpid(last_child, &o->last_status, 0);
	if (WIFSIGNALED(o->last_status))
	{
		o->last_status = WTERMSIG(o->last_status);
		if (o->last_status == 2)
			o->last_status = 130;
		else
			o->last_status = 131;
	}
	else
		o->last_status = WEXITSTATUS(o->last_status);
}
