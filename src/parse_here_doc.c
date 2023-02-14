/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:56:11 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/14 12:49:36 by luntiet-         ###   ########.fr       */
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
	if (!ft_strncmp(line, deli, ft_strlen(deli))
		&& ft_strlen(deli) == ft_strlen(line))
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

static char	*handle_delimiter(char *deli, int *replace)
{
	if (!ft_strncmp(deli, "\\\"", ft_strlen(deli))
		|| !ft_strncmp(deli, "\\\'", ft_strlen(deli)))
		deli = str_remove_char(deli, '\\');
	else if (single_quote_count(deli) < 2 && quote_count(deli) < 2)
	{
		deli = str_remove_char(deli, '\'');
		deli = str_remove_char(deli, '\"');
		return (deli);
	}
	else if (single_quote_count(deli) % 2 == 0 && single_quote_count(deli) > 0)
		deli = str_remove_char(deli, '\'');
	else if (quote_count(deli) % 2 == 0 && quote_count(deli) > 0)
		deli = str_remove_char(deli, '\"');
	*replace = 0;
	return (deli);
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
	if (!ft_strchr(deli, '\'') || !ft_strchr(deli, '\"'))
		deli = handle_delimiter(deli, &replace);
	run = 1;
	child = fork();
	if (child == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		while (run)
			run = handle_heredoc(o, deli, replace, fd);
		free_options(o);
		free(deli);
		exit(0);
	}
	return (free(deli), close(fd), waitpid(child, NULL, 0), NULL);
}
