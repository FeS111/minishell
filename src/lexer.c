/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:55:53 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/07 13:55:55 by fschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*get_word(char *charset)
{
	int	i;

	i = 0;
	while (!is_whitespace(charset[i]) && !ft_strchr("|<>#", charset[i]))
	{
		if (charset[i] == '\'' || charset[i] == '\"')
			i += quote_len(&charset[i]);
		i++;
	}
	if (i == 0)
		return (NULL);
	return (new_token(ft_substr(charset, 0, i), WORD));
}

t_token	*get_token(char *charset)
{
	if (charset[0] == ' ')
		return (NULL);
	if (ft_strchr("\n\0", charset[0]))
		return (NULL);
	else if (charset[0] == '\'' || charset[0] == '\"')
		return (get_quoted(charset));
	else if (charset[0] == '-' && getafter_option(charset) > 1)
		return (get_option(charset));
	else if (ft_strchr("><#", charset[0]))
		return (get_io(charset));
	else if (charset[0] == '|')
		return (get_pipe(charset));
	else
		return (get_word(charset));
	return (NULL);
}

int	lexer(t_options *o)
{
	t_token	**tokens;
	int		i;
	int		j;

	if (!ft_strlen(o->line))
		return (-1);
	i = 0;
	j = 0;
	tokens = ft_calloc(sizeof(t_token *), 1024);
	while (o->line[i])
	{
		tokens[j] = get_token(&(o->line)[i]);
		if (tokens[j])
		{
			i += ft_strlen(tokens[j]->value);
			j++;
			continue ;
		}
		i++;
	}
	o->tokens = tokens;
	return (0);
}
