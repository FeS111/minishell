/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:49:55 by fschmid           #+#    #+#             */
/*   Updated: 2023/01/13 17:01:53 by fschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	getnext_whitespace(char *str)
{
	size_t	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (ft_strchr(" \t\r\v\f", str[i]))
			return (i);
	}
	return (0);
}
