/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:56:35 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/10 15:24:37 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

int	get_out_fd(t_parse_table **tables, int i)
{
	while (i >= 0)
	{
		if (tables[i]->out == WRITE && tables[i]->cmd->cmd)
		{
			if (tables[i]->cmd->args && tables[i]->cmd->args[0]
				&& !ft_strncmp(tables[i]->cmd->args[0], ">>", 2))
				return (open(tables[i]->cmd->cmd,
						O_APPEND | O_WRONLY, 0644));
			return (open(tables[i]->cmd->cmd,
					O_CREAT | O_TRUNC | O_WRONLY, 0644));
		}
		i--;
	}
	return (STD_OUTPUT);
}

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
