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
			line = replace_home(line, i);
	}
	return (line);
}

static int	handle_heredoc(t_options *o, char *deli, int replace, int fd)
{
	char	*line;

	line = readline("heredoc> ");
	if (!line || !ft_strncmp(line, deli,
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

t_parse_cmd	*here_doc(t_options *o, int *in, int *out, int *i)
{
	int		fd;
	int		replace;
	int		run;
	char	*deli;

	replace = 1;
	*in = READ;
	*out = STDOUT_FILENO;
	if (o->tokens[*i + 2] && o->tokens[*i + 2]->type == PIPE)
		*out = PIPE_FD;
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
	*i += 2;
	return (new_cmd(ft_strdup("here_doc"), NULL, NULL, NULL));
}
