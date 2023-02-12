/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:56:35 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/12 11:30:59 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_options	*create_options(void)
{
	t_options	*o;
	int			i;
	int			size;
	extern char	**environ;

	size = 0;
	while (environ[size] != NULL)
		size++;
	o = malloc(sizeof(t_options));
	if (!o)
		return (NULL);
	i = -1;
	o->env = malloc(sizeof(char *) * (size + 1));
	while (environ[++i] != NULL)
		o->env[i] = ft_strdup(environ[i]);
	o->env[i] = NULL;
	o->pwd = get_pwd();
	o->line = NULL;
	o->tokens = NULL;
	o->paths = get_paths(o);
	o->is_shell = isatty(0);
	return (o);
}

void	free_options(t_options *o)
{
	free(o->pwd);
	free(o->line);
	if (o->tokens)
		free_tokens(o->tokens);
	if (o->tables)
		free_table(o->tables);
	split_free(o->env);
	split_free(o->paths);
	free(o);
}

void	close_fd(int *fd)
{
	close(fd[0]);
	if (fd[1] != STDOUT_FILENO)
		close (fd[1]);
}
