/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:56:08 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/11 13:13:33 by luntiet-         ###   ########.fr       */
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

t_parse_cmd	*handle_io(t_options *o, int *in, int *out, int *i)
{
	if (!ft_strncmp(o->tokens[*i]->value, "<<", 3))
	{
		if (!o->tokens[*i + 1] || o->tokens[*i + 1]->type == IO)
			return (redir_panic(o, i), NULL);
		return (here_doc(o, in, out, i));
	}
	else if (!ft_strncmp(o->tokens[*i]->value, "<", 2))
	{
		if (!o->tokens[*i + 1] || o->tokens[*i + 1]->type != WORD)
			return (redir_panic(o, i), NULL);
		return (left_redir(o->tokens, in, out, i));
	}
	else if (!ft_strncmp(o->tokens[*i]->value, ">", 1))
		return (right_redir(o->tokens, in, out, i));
	return (NULL);
}

t_parse_cmd	*join_args(t_token **tokens, int *i, char *word)
{
	char		*tmp;
	char		**tmp3;
	int			j;

	tmp = NULL;
	tmp3 = ft_calloc(sizeof(char *), token_size(tokens) + 1);
	j = -1;
	while (tokens[*i])
	{
		if (tokens[*i] && tokens[*i]->type == OPTION)
		{
			if (tmp)
				tmp = ft_strjoin_gnl(tmp, " ");
			tmp = ft_strjoin_gnl(tmp, tokens[*i]->value);
		}
		if (tokens[*i] && is_woo2(tokens[*i]->type))
			tmp3[++j] = ft_strdup(tokens[*i]->value);
		if (tokens[*i] && !is_woo2(tokens[*i]->type))
			break ;
		*i += 1;
	}
	return (new_cmd(word, tmp, NULL, tmp3));
}

t_parse_cmd	*handle_token(t_token **tokens, int *in, int *out, int *i)
{
	t_parse_cmd	*new;
	char		*word;

	word = NULL;
	*out = STD_OUTPUT;
	if (*i > 0 && tokens[*i]->value && tokens[*i - 1]->type == PIPE)
		*in = PIPE_FD;
	if (tokens[*i]->type != IO)
	{
		word = ft_strdup(tokens[*i]->value);
		*i += 1;
	}
	new = join_args(tokens, i, word);
	if (tokens[*i] && tokens[*i]->type == PIPE)
		*out = PIPE_FD;
	if (tokens[*i] && tokens[*i]->type == IO)
	{
		new->infile = get_infile(tokens, i, in);
		if (!new->infile)
			*in = STD_INPUT;
		new->outfile = get_outfile(tokens, i, out);
		if (!new->outfile)
			*out = STD_OUTPUT;
		*i += 1;
	}
	return (new);
}
