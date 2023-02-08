/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luntiet- <luntiet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:55:18 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/08 10:20:20 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>

void	panic(t_options *o, int code)
{
	ft_putendl_fd("exit", 1);
	free_options(o);
	exit(code);
}

void	ft_pwd(t_options *o)
{
	ft_putendl_fd(o->pwd, 1);
	o->last_status = 0;
}

void	ft_env(t_options *o)
{
	int				i;

	i = -1;
	while (o->env[++i] != NULL)
		ft_putendl_fd(o->env[i], 1);
	o->last_status = 0;
}

void	ft_unset(t_options *o, t_parse_cmd *cmd)
{
	remove_env(o, cmd->args[0]);
	o->last_status = 0;
}

void	ft_echo(t_options *o, t_parse_cmd *cmd)
{
	int		l;
	char	*tmp;

	l = 0;
	while (cmd->args[l])
		l++;
	if (cmd->opt && ft_strncmp(cmd->opt, "-n", 2) == 0)
	{
		tmp = strjoinn(cmd->args, " ", 1, l);
		ft_putstr_fd(tmp, 1);
	}
	else
	{
		tmp = strjoinn(cmd->args, " ", 0, l);
		ft_putendl_fd(tmp, 1);
	}
	free(tmp);
	o->last_status = 0;
}
