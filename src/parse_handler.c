/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:56:08 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/12 13:15:24 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	redir_panic(t_options *o, int *i)
{
	o->last_status = 258;
	if (!o->tokens[*i + 1])
		panic_token("`newline'");
	else
		panic_token(o->tokens[*i + 1]->value);
}

t_parse_cmd	*check_first_io(t_options *o, int *i, int *in, int *out)
{
	t_parse_cmd *new;
	char		*infile;
	char		*outfile;

	new = new_cmd(NULL, NULL, NULL, NULL);
	infile = NULL;
	outfile = NULL;
	if (o->tokens[*i]->type == IO)
	{
		infile = get_infile(o, i, in);
		outfile = get_outfile(o, i, out);
		*i += 2;
	}
	if (o->tokens[*i] && o->tokens[*i]->type == PIPE)
		*out = PIPE;
	new->infile = infile;
	new->outfile = outfile;
	return (new);
}

t_parse_cmd	*handle_token(t_options *o, int *in, int *out, int *i)
{
	t_parse_cmd	*new;
	int			j;

	j = -1;
	new = NULL;
	*out = STD_OUTPUT;
	if (*i > 0 && o->tokens[*i]->value && o->tokens[*i - 1]->type == PIPE)
		*in = PIPE_FD;
	new = check_first_io(o, i, in, out);
	if (o->tokens[*i] && o->tokens[*i]->type == PIPE)
		return (new);
	if (o->tokens[*i])
	{
		 ft_putendl_fd("here", 1);
		 new->cmd = ft_strdup(o->tokens[*i]->value);
		 new->args = ft_calloc(sizeof(char *), token_size(o->tokens) + 1);
		 *i += 1;
	}
	while (o->tokens[*i] && o->tokens[*i]->type != PIPE)
	{
		if (o->tokens[*i]->type == IO)
		{
			new->infile = get_infile(o, i, in);
			new->outfile = get_outfile(o, i, out);
			*i += 2;
			continue ;
		}
		if (o->tokens[*i] && o->tokens[*i]->type == OPTION)
		{
			if (new->opt)
				new->opt = ft_strjoin_gnl(new->opt, " ");
			new->opt = ft_strjoin_gnl(new->opt, o->tokens[*i]->value);
		}
		if (o->tokens[*i] && is_woo2(o->tokens[*i]->type))
			new->args[++j] = ft_strdup(o->tokens[*i]->value);
		*i += 1;
	}
	return (new);
}
