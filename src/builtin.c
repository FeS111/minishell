/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:55:09 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/10 18:07:30 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	g_global;

static int	validate_export(t_parse_cmd *cmd)
{
	char	**tmp;
	char	*err;

	if (ft_strchr("+=-*&^%$#!{}[]@", cmd->args[0][0]))
	{
		err = ft_strjoin("export: '", cmd->args[0]);
		err = ft_strjoin_gnl(err, "': not a valid identifier");
		ft_putendl_fd(err, 2);
		free(err);
		g_global.status = 256;
		return (0);
	}
	tmp = ft_split(cmd->args[0], '=');
	if (tmp[0][0] && ft_isdigit(tmp[0][0]))
	{
		err = ft_strjoin("export: '", cmd->args[0]);
		err = ft_strjoin_gnl(err, "': not a valid identifier");
		ft_putendl_fd(err, 2);
		free(err);
		g_global.status = 256;
		split_free(tmp);
		return (0);
	}
	split_free(tmp);
	return (1);
}

void	ft_export(t_options *o, t_parse_cmd *cmd)
{
	char	**tmp;

	if (!cmd->args || !cmd->args[0])
		return (print_export_error(o));
	if (!validate_export(cmd))
		return ;
	tmp = split_first(cmd->args[0], '=');
	if (tmp && tmp[0])
	{
		remove_env(o, tmp[0]);
		add_env(o, tmp[0], tmp[1]);
		split_free(tmp);
		g_global.status = 0;
	}
}

static int	find_git(void)
{
	int		i;
	int		fd;
	char	*pwd;
	char	*tmp;

	i = 0;
	pwd = ft_strdup(".git/HEAD");
	fd = open(pwd, O_RDONLY);
	while (fd < 2 && i < 20)
	{
		tmp = ft_strjoin("../", pwd);
		free(pwd);
		pwd = tmp;
		fd = open(pwd, O_RDONLY);
		i++;
	}
	free(pwd);
	return (fd);
}

static char	*get_current_branch(void)
{
	char	**tmp;
	char	*res;
	char	*line;
	int		i;
	int		fd;

	fd = find_git();
	if (fd < 2)
		return (NULL);
	line = read_first_line(fd);
	close(fd);
	if (!line)
		return (NULL);
	tmp = ft_split(line, '/');
	free(line);
	i = 0;
	while (tmp[i])
		i++;
	res = ft_strtrim(tmp[i -1], "\n");
	split_free(tmp);
	return (res);
}

char	*get_current_folder(char *pwd)
{
	char	**tmp;
	char	*res;
	int		i;
	char	*branch;

	tmp = ft_split(pwd, '/');
	i = 0;
	while (tmp[i])
		i++;
	res = show_status();
	if (i == 0)
		res = ft_strjoin_gnl(res, "/");
	else
		res = ft_strjoin_gnl(res, tmp[i - 1]);
	branch = get_current_branch();
	if (branch)
	{
		res = ft_strjoin_gnl(res, " \033[0;35mgit:(");
		res = ft_strjoin_gnl(res, "\033[31m");
		res = replace_join(res, branch);
		res = ft_strjoin_gnl(res, "\033[0;35m)\033[0;0m");
	}
	res = ft_strjoin_gnl(res, " > ");
	return (split_free(tmp), res);
}
