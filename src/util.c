/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:49:55 by fschmid           #+#    #+#             */
/*   Updated: 2023/01/13 16:55:36 by fschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	getnext_whitespace(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (ft_strchr(" \t\r\v\f", str[i]))
			return (i);
	}
	return (0);
}