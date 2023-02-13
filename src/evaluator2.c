/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:55:36 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/12 14:14:19 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*handle_arg(t_options *o, t_eval eval)
{
	if (eval.arg[eval.j] == '"'
		&& !*(eval.double_quotes) && *(eval.replace))
		*(eval.double_quotes) = 1;
	else if (eval.arg[eval.j] == '\''
		&& *(eval.replace) && !*(eval.double_quotes))
		*(eval.replace) = 0;
	else if (eval.arg[eval.j] == '\''
		&& !*(eval.replace) && !*(eval.double_quotes))
		*(eval.replace) = 1;
	if (!*(eval.replace))
		return (eval.arg);
	if (eval.arg[eval.j] == '$' && eval.arg[eval.j + 1] != '\0')
		eval.arg
			= replace_variable(o, eval.arg, eval.j,
				get_varlength(&eval.arg[eval.j]));
	return (eval.arg);
}

void	evaluator_args(t_options *o, int i)
{
	int		k;
	int		j;
	int		replace;
	int		double_quotes;
	t_eval	eval;

	replace = 1;
	double_quotes = 0;
	eval.replace = &replace;
	eval.double_quotes = &double_quotes;
	k = -1;
	while (o->tables[i]->cmd->args && o->tables[i]->cmd->args[++k])
	{
		j = -1;
		while (o->tables[i]->cmd->args[k]
			&& o->tables[i]->cmd->args[k][++j] != '\0')
		{
			eval.j = j;
			eval.arg = o->tables[i]->cmd->args[k];
			o->tables[i]->cmd->args[k]
				= handle_arg(o, eval);
		}
		o->tables[i]->cmd->args[k]
			= remove_quotes(o->tables[i]->cmd->args[k]);
	}
}

void	evaluator_cmd(t_options *o, int i)
{
	int		j;
	int		replace;
	int		double_quotes;
	t_eval	eval;

	replace = 1;
	double_quotes = 0;
	eval.replace = &replace;
	eval.double_quotes = &double_quotes;
	j = -1;
	while (o->tables[i]->cmd->cmd && o->tables[i]->cmd->cmd[++j])
	{
		eval.j = j;
		eval.arg = o->tables[i]->cmd->cmd;
		o->tables[i]->cmd->cmd = handle_arg(o, eval);
	}
	if (o->tables[i]->cmd->cmd)
		o->tables[i]->cmd->cmd = remove_quotes(o->tables[i]->cmd->cmd);
}
