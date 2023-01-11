/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luntiet- <luntiet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:26:45 by fschmid           #+#    #+#             */
/*   Updated: 2023/01/11 17:14:15 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int is_command(char *input)
{
	input = NULL;
	return (0);
}

int	main(void)
{
	char	*input;
	int		history_fd;

	history_fd = open(".minishell_history", O_CREAT | O_WRONLY, 0600);
	while (1)
	{
		write(1, "minishell > ", 12);
		input = get_next_line(0);
		if (is_command(input))
			write(history_fd, input, ft_strlen(input));
		free(input);
	}
	return (0);
}
