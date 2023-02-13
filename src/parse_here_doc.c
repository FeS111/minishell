/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:56:11 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/12 14:49:34 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*evalulate(t_options *o, char *line)
{
	int	i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == '$')
			line = replace_variable(o, line, i, get_varlength(&line[i]));
		else if (line[i] == '~')
			line = replace_home(o, line, i);
	}
	return (line);
}

static int	handle_heredoc(t_options *o, char *deli, int replace, int fd)
{
	char	*line;

	line = readline("heredoc> ");
	if (!line || !ft_strncmp(line, deli,
			ft_strlen(line)))
		return (free(line), 0);
	if (line && *line)
	{
		if (replace)
			line = evalulate(o, line);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (1);
}

t_parse_cmd	*here_doc(t_options *o, int *in, int *i)
{
	int		fd;
	int		replace;
	int		run;
	char	*deli;

	replace = 1;
	in[0] = HEREDOC;
	fd = open("here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	deli = ft_strdup(o->tokens[*i + 1]->value);
	if (ft_strchr("'\"", deli[0]) && ft_strchr("'\"", deli[ft_strlen(deli) - 1]))
	{
		replace = 0;
		free(deli);
		deli = ft_strtrim(o->tokens[*i + 1]->value, "'\"");
	}
	run = 1;
	while (run)
		run = handle_heredoc(o, deli, replace, fd);
	free(deli);
	close(fd);
	return (NULL);
}
