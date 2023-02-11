/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handler_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:56:01 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/11 15:57:34 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_infile(t_token **tokens, int *i, int *in)
{
	if (!tokens[*i])
		return (NULL);
	if (!ft_strncmp(tokens[*i]->value, "<", 2))
	{
		*in = READ;
		return (tokens[*i + 1]->value);
	}
	else if (!ft_strncmp(tokens[*i]->value, "<<", 3))
	{
		*in = HEREDOC;
		return (tokens[*i + 1]->value);
	}
	return (NULL);
}

char	*get_outfile(t_token **tokens, int *i, int *out)
{
	int	fd;

	if (!tokens[*i])
		return (NULL);
	if (!ft_strncmp(tokens[*i]->value, ">", 2))
	{
		*out = WRITE;
		fd = open(tokens[*i + 1]->value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		close(fd);
		return (tokens[*i + 1]->value);
	}
	else if (!ft_strncmp(tokens[*i]->value, ">>", 3))
	{
		*out = APPEND;
		fd = open(tokens[*i + 1]->value, O_CREAT | O_WRONLY, 0644);
		close(fd);
		return (tokens[*i + 1]->value);
	}
	return (NULL);
}

t_parse_cmd	*left_redir(t_token **tokens, int *in, int *out, int *i)
{
	*out = STD_OUTPUT;
	*i += 1;
	*in = READ;
	return (new_cmd(ft_strdup(tokens[*i]->value), NULL, NULL, NULL));
}

t_parse_cmd	*right_redir(t_token **tokens, int *in, int *out, int *i)
{
	if (tokens[*i + 1])
	{
		*i += 1;
		*out = WRITE;
		*in = STD_INPUT;
		if (!ft_strncmp(tokens[*i - 1]->value, ">>", 3))
			return (new_cmd(ft_strdup(tokens[*i]->value), NULL, NULL,
					ft_split(tokens[*i - 1]->value, 0)));
		return (new_cmd(ft_strdup(tokens[*i]->value), NULL, NULL, NULL));
	}
	else
		return (panic_token("`newline'"), NULL);
	return (NULL);
}
