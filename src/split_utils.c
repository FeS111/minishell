/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:17:07 by luntiet-          #+#    #+#             */
/*   Updated: 2023/01/13 10:52:53 by fschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	split_free(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

char	*strjoinn(char **arr, char *c, int start, int end)
{
	int		i;
	char	*res;
	char	*tmp;

	res = ft_calloc(sizeof(char), 1);
	i = start;
	while (arr[i] != NULL && i <= end)
	{
		tmp = ft_strjoin(res, arr[i]);
		free(res);
		res = ft_strdup(tmp);
		free(tmp);
		if (i < end)
		{
			tmp = ft_strjoin(res, c);
			free(res);
			res = ft_strdup(tmp);
			free(tmp);
		}
		i++;
	}
	return (res);
}

char	**split_join(char **str)
{
	char	**new;
	int		i;
	char	*tmp;

	if (!str)
		return (NULL);
	new = malloc(3 * sizeof(char *));
	i = 1;
	new[0] = str[0];
	tmp = ft_strdup("");
	while (str[i])
	{
		tmp = ft_strjoin_gnl(tmp, str[i]);
		i++;
		if (str[i])
			tmp = ft_strjoin_gnl(tmp, " ");
	}
	new[1] = tmp;
	new[2] = NULL;
	return (free (str), new);
}
