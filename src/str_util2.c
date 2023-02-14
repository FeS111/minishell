/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:30:39 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/14 08:08:32 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*strtrim_front(char *str, char *set)
{
	int		i;
	int		j;
	char	*res;
	char	*tmp;

	i = 0;
	tmp = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	while (str[i] != '\0' && ft_strchr(set, str[i]))
		++i;
	i -= 1;
	j = -1;
	while (str[++i] != '\0')
		tmp[++j] = str[i];
	res = ft_strdup(tmp);
	free(tmp);
	return (res);
}

int	split_size(char **split)
{
	int	i;

	i = 0;
	while (split && split[i])
		i++;
	return (i);
}

int	count_occurrence(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
