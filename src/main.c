/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:26:45 by fschmid           #+#    #+#             */
/*   Updated: 2023/01/13 12:13:49 by fschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	char	*line;
	t_token	*tokens;
	int		i;

	ft_printf("%d\n", is_word("test", 1));

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
		tokens = lexer(line);
		i++;
		free(line);
	}
	return (0);
}
