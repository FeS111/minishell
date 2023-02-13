/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luntiet- <luntiet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:55:39 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/13 15:08:16 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_in(t_parse_table *table)
{
	if (table->in == READ)
		return (open(table->cmd->infile, O_RDONLY));
	else if (table->in == HEREDOC)
		return (open("here_doc", O_RDONLY));
	return (dup(STDIN_FILENO));
}

int	get_out(t_parse_table *table)
{
	if (table->out == WRITE)
		return (open(table->cmd->outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644));
	else if (table->out == APPEND)
		return (open(table->cmd->outfile, O_CREAT | O_APPEND, 0644));
	return (STDOUT_FILENO);
}

char	**get_paths(t_options *o)
{
	char	*path;
	char	**res;

	path = ft_getenv(o, "PATH");
	if (!path)
		return (NULL);
	res = ft_split(path, ':');
	free(path);
	return (res);
}

char	*search_binary(t_options *o, char *cmd)
{
	char	*absolute_path;
	int		i;

	if (!ft_strlen(cmd))
		return (ft_putendl_fd(" : command not found", 2), NULL);
	if (cmd[0] == '/' && access(cmd, X_OK) >= 0)
		return (ft_strdup(cmd));
	if (!ft_strncmp(cmd, "./", 2))
		return (ft_strdup(cmd));
	i = 0;
	split_free(o->paths);
	o->paths = get_paths(o);
	while (o->paths && o->paths[i])
	{
		absolute_path = ft_strjoin(o->paths[i], "/");
		absolute_path = ft_strjoin_gnl(absolute_path, cmd);
		if (access(absolute_path, F_OK) >= 0)
			return (absolute_path);
		free(absolute_path);
		i++;
	}
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	return (NULL);
}

char	**build_args(t_parse_cmd *cmd)
{
	char	**args;
	int		i;
	int		l;

	l = 0;
	while (cmd->args && cmd->args[l])
		l++;
	args = ft_calloc(sizeof(char *), l + 2);
	i = 0;
	args[0] = ft_strdup(cmd->cmd);
	l = -1;
	while (cmd->args && cmd->args[++l])
		args[++i] = ft_strdup(cmd->args[l]);
	return (args);
}
