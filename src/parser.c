/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luntiet- <luntiet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:41:41 by luntiet-          #+#    #+#             */
/*   Updated: 2023/01/12 16:11:18 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*piped_tokens(char **piped)
{
	int 	i;
	char	**cmd;
	t_token	*tokens;
	t_token token;

	i = 0;
	tokens = malloc(sizeof(t_token));
	while (piped[i])
	{
		cmd = ft_split(piped[i], ' ');
		token.cmd = cmd[0];
		token.args = &cmd[1];
		tokens[i] = token;
		i++;
	}
	return (tokens);
}

t_token	*parse_input(char *line)
{
	char	**cmd;
	char	**piped;
	t_token	*tokens;
	t_token	tmp;

	if (!line)
		return (NULL);
	if (ft_strchr(line, '|'))
	{
		piped = ft_split(line, '|');
		return (piped_tokens(piped));
	}
	cmd = ft_split(line, ' ');
	tmp.cmd = cmd[0];
	tmp.args = &cmd[1];
	tokens = malloc(sizeof(t_token));
	tokens[0] = tmp;
	return (tokens);
}
