/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luntiet- <luntiet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 11:41:41 by luntiet-          #+#    #+#             */
/*   Updated: 2023/01/12 12:27:31 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*parse_input(char *line)
{
	char	**cmd;
	t_token	*tokens;
	t_token	tmp;

	if (!line)
		return (NULL);
	cmd = ft_split(line, ' ');
	tmp.cmd = cmd[0];
	tmp.args = &cmd[1];
	tokens = malloc(sizeof(t_token));
	tokens[0] = tmp;
	return (tokens);
}
