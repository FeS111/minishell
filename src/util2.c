/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:56:39 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/07 13:56:42 by fschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_pwd(void)
{
	char	*cwd;

	cwd = ft_calloc(sizeof(char), PATH_MAX);
	getcwd(cwd, PATH_MAX);
	return (cwd);
}

size_t	getnext_whitespace(char *str)
{
	size_t	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (is_whitespace(str[i + 1]) || str[i + 1] == '\0')
			return (i + 1);
	}
	return (0);
}

size_t	getafter_option(char *str)
{
	size_t	i;

	i = 1;
	while (!is_whitespace(str[i]) && !ft_strchr("|<>&\0", str[i]))
		i++;
	return (i);
}

int	is_whitespace(char c)
{
	if (ft_strchr(" \t\r\v\f\n", c))
		return (1);
	return (0);
}
