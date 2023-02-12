/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:56:18 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/12 11:20:20 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_pipes(t_token **tokens)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == PIPE)
			count++;
		i++;
	}
	return (count);
}

void	set_fd(int *fd)
{
	fd[0] = 0;
	fd[1] = 1;
}

int	parser(t_options *o)
{
	int				i;
	int				j;
	t_parse_table	**tables;
	int				fd[2];

	i = 0;
	j = 0;
	set_fd(fd);
	tables = ft_calloc(sizeof(t_parse_table *), token_size(o->tokens) + 1);
	o->pipes = count_pipes(o->tokens);
	while (o->tokens[i])
	{
		tables[j] = new_table(build_cmd(o, &fd[0], &fd[1], &i), fd[0], fd[1]);
		if (!tables[j])
		{
			o->tables = tables;
			return (-1);
		}
		set_fd(fd);
		j++;
		i++;
	}
	tables[j] = NULL;
	o->tables = tables;
	return (0);
}
