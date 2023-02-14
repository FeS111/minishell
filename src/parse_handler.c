/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:56:08 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/14 09:16:25 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	g_global;

void	redir_panic(t_options *o, int *i)
{
	g_global.status = 258;
	if (!o->tokens[*i + 1])
		panic_token("`newline'");
	else
		panic_token(o->tokens[*i + 1]->value);
}

t_parse_cmd	*check_io(t_options *o, int *i, int *fd)
{
	t_parse_cmd	*new;
	char		*infile;
	char		*outfile;

	infile = NULL;
	outfile = NULL;
	if (o->tokens[*i]->type == IO)
	{
		infile = get_infile(o, i, fd, infile);
		outfile = get_outfile(o, i, fd, outfile);
		*i += 2;
	}
	new = new_cmd(NULL, NULL, NULL, NULL);
	if (o->tokens[*i] && o->tokens[*i]->type == PIPE)
		fd[1] = PIPE;
	if (o->tokens[*i] && o->tokens[*i]->type == IO)
		check_io(o, i, fd);
	new->infile = infile;
	new->outfile = outfile;
	return (new);
}

void	get_args(t_options *o, t_parse_cmd *new, int *i, int *fd)
{
	int	j;

	j = -1;
	while (o->tokens[*i] && o->tokens[*i]->type != PIPE)
	{
		if (o->tokens[*i]->type == IO)
		{
			new->infile = get_infile(o, i, fd, new->infile);
			new->outfile = get_outfile(o, i, fd, new->outfile);
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
}

t_parse_cmd	*handle_token(t_options *o, int *fd, int *i)
{
	t_parse_cmd	*new;

	new = NULL;
	fd[1] = STD_OUTPUT;
	if (*i > 0 && o->tokens[*i]->value && o->tokens[*i - 1]->type == PIPE)
		fd[0] = PIPE_FD;
	new = check_io(o, i, fd);
	if (o->tokens[*i] && o->tokens[*i]->type == PIPE)
		return (new);
	if (o->tokens[*i])
	{
		new->cmd = ft_strdup(o->tokens[*i]->value);
		new->args = ft_calloc(sizeof(char *), token_size(o->tokens) + 1);
		*i += 1;
	}
	get_args(o, new, i, fd);
	return (new);
}
