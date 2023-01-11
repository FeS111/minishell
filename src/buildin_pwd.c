/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:01:52 by fschmid           #+#    #+#             */
/*   Updated: 2023/01/11 17:15:42 by fschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*pwd(void)
{
	char	*cwd;

	cwd = ft_calloc(sizeof(char), PATH_MAX);
	getcwd(cwd, PATH_MAX);
	return (cwd);
}
