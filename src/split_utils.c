/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luntiet- <luntiet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:17:07 by luntiet-          #+#    #+#             */
/*   Updated: 2023/01/12 15:34:49 by luntiet-         ###   ########.fr       */
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
