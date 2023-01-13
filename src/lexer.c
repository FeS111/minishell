/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:41:41 by luntiet-          #+#    #+#             */
/*   Updated: 2023/01/13 17:18:33 by fschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*piped_tokens(char **piped)
{
	int		i;
	char	**cmd;
	t_token	**tokens;

	i = 0;
	tokens = malloc(sizeof(t_token));
	while (piped[i])
	{
		cmd = ft_split(piped[i], ' ');
		i++;
	}
	return (tokens);
}

t_token	*lexer(char *line)
{
	char	**cmd;
	t_token	**tokens;

	if (!line)
		return (NULL);
	if (ft_strchr(line, '|'))
		return (piped_tokens(ft_split(line, '|')));
	cmd = ft_split(line, ' ');
	tokens = malloc(sizeof(t_token *));
	return (tokens);
}
