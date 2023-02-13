/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:56:15 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/13 13:14:59 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_parse_cmd	*build_cmd(t_options *o, int *fd, int *i)
{
	if (o->tokens[*i]->type == PIPE)
	{
		if (*i == 0)
			return (panic_token("`|'"), NULL);
		else
			*i += 1;
	}
	else if (o->tokens[0]->type == IO && !o->tokens[1])
		return (panic_token("`newline'"), NULL);
	else if (o->tokens[0]->type == IO && o->tokens[1]->type != WORD)
		return (panic_token(o->tokens[*i + 1]->value), NULL);
	return (handle_token(o, fd, i));
}

t_parse_table	*new_table(t_parse_cmd *cmd, int in, int out)
{
	t_parse_table	*new;

	if (!cmd)
		return (NULL);
	new = malloc(sizeof(t_parse_table));
	new->cmd = cmd;
	new->in = in;
	new->out = out;
	return (new);
}

void	free_cmd(t_parse_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->cmd != NULL)
		free(cmd->cmd);
	ft_putendl_fd("free_cmd", 2);
	if (cmd->opt)
		free(cmd->opt);
	if (cmd->opt2)
		free(cmd->opt2);
	if (cmd->args)
		split_free(cmd->args);
	free(cmd);
}

void	free_table(t_parse_table **table)
{
	int	i;
	int	j;

	i = 0;
	if (!table)
		return ;
	while (table[i])
	{
		j = 0;
		if (table[i]->cmd)
			free_cmd(table[i]->cmd);
		if (table[i]->in > 2)
			close(table[i]->in);
		if (table[i]->out > 2)
			close(table[i]->out);
		free(table[i]);
		i++;
	}
	free(table);
}
