/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handler_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:56:01 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/12 12:57:39 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_infile(t_options *o, int *i, int *in)
{
	if (!o->tokens[*i])
		return (NULL);
	if (!ft_strncmp(o->tokens[*i]->value, "<", 2))
	{
		*in = READ;
		return (o->tokens[*i + 1]->value);
	}
	else if (!ft_strncmp(o->tokens[*i]->value, "<<", 3))
	{
		here_doc(o, in, i);
		return ("here_doc");
	}
	return (NULL);
}

char	*get_outfile(t_options *o, int *i, int *out)
{
	int	fd;

	if (!o->tokens[*i])
		return (NULL);
	if (!ft_strncmp(o->tokens[*i]->value, ">", 2))
	{
		*out = WRITE;
		fd = open(o->tokens[*i + 1]->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		close(fd);
		return (o->tokens[*i + 1]->value);
	}
	else if (!ft_strncmp(o->tokens[*i]->value, ">>", 3))
	{
		*out = APPEND;
		fd = open(o->tokens[*i + 1]->value, O_CREAT | O_WRONLY, 0644);
		close(fd);
		return (o->tokens[*i + 1]->value);
	}
	return (NULL);
}
