/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handler_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:56:01 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/14 12:51:00 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	g_global;

char	*get_infile(t_options *o, int *i, int *fd, char *infile)
{
	if (!o->tokens[*i])
		return (infile);
	if (!ft_strncmp(o->tokens[*i]->value, "<", 2))
	{
		fd[0] = READ;
		return (o->tokens[*i + 1]->value);
	}
	else if (!ft_strncmp(o->tokens[*i]->value, "<<", 3))
	{
		g_global.mode = 2;
		here_doc(o, fd, i);
		if (g_global.mode == 2)
			g_global.mode = 0;
		return ("here_doc");
	}
	return (infile);
}

char	*get_outfile(t_options *o, int *i, int *fd, char *outfile)
{
	int	outfd;

	if (!o->tokens[*i])
		return (outfile);
	if (!ft_strncmp(o->tokens[*i]->value, ">", 2))
	{
		fd[1] = WRITE;
		outfd = open(o->tokens[*i + 1]->value,
				O_CREAT | O_TRUNC | O_WRONLY, 0644);
		close(outfd);
		return (o->tokens[*i + 1]->value);
	}
	else if (!ft_strncmp(o->tokens[*i]->value, ">>", 3))
	{
		fd[1] = APPEND;
		outfd = open(o->tokens[*i + 1]->value, O_CREAT | O_WRONLY, 0644);
		close(outfd);
		return (o->tokens[*i + 1]->value);
	}
	return (outfile);
}
