/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:26:45 by fschmid           #+#    #+#             */
/*   Updated: 2023/01/13 11:48:04 by fschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char	*line;
	t_token	*tokens;
	int		i;

	i = 0;
	while (1)
	{
		line = readline("minishell> ");
		if (line && *line)
			add_history(line);
		if (!ft_strncmp(line, "exit", 4))
		{
			ft_putendl_fd("exit", 1);
			free(line);
			return (0);
		}
		tokens = parse_input(line);
		//ft_putendl_fd(tokens[0].cmd, 1);
		//if (tokens[1].cmd)
		//	ft_putendl_fd(tokens[1].cmd, 1);
		i++;
		free(line);
	}
	return (0);
}
