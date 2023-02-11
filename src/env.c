/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:55:24 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/10 20:25:08 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_env(t_options *o, char *name, char *value)
{
	int		i;
	int		size;
	char	**env;

	size = 0;
	if (!value)
		return ;
	while (o->env[size] != NULL)
		size++;
	env = malloc(sizeof(char *) * (size + 2));
	i = -1;
	while (o->env[++i] != NULL)
		env[i] = ft_strdup(o->env[i]);
	size = 0;
	env[i] = ft_strjoin_gnl(ft_strjoin(name, "="), value);
	env[i + 1] = NULL;
	split_free(o->env);
	o->env = env;
}

void	remove_env(t_options *o, char *name)
{
	int		i;
	int		j;
	int		size;
	char	**env;

	size = 0;
	while (o->env[size] != NULL)
		size++;
	env = malloc(sizeof(char *) * (size + 1));
	i = -1;
	j = 0;
	while (o->env[++i] != NULL)
	{
		if (!ft_strnstr(o->env[i], name, ft_strlen(name)))
				// ft_strchr(o->env[i], '=') - o->env[i]) + 1)
		{
			env[j] = ft_strdup(o->env[i]);
			j++;
		}
	}
	env[j] = NULL;
	split_free(o->env);
	o->env = env;
}
