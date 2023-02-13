/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:56:11 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/13 19:21:16 by luntiet-         ###   ########.fr       */
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
	}
	return (line);
}

static int	handle_heredoc(t_options *o, char *deli, int replace, int fd)
{
	char	*line;

	line = readline("heredoc> ");
	if (!ft_strncmp(line, deli,
			ft_strlen(deli)))
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
	pid_t	child;

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
	child = fork();
	if (child == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		while (run)
			run = handle_heredoc(o, deli, replace, fd);
		wait(NULL);
		exit(0);
	}	
	return (waitpid(child, NULL, 0), free(deli), close(fd), NULL);
}
