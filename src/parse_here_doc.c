#include "../include/parser.h"
#include <unistd.h>

char	**here_doc(t_token **tokens, int *in, int *out, int *i)
{
	int		fd;
	char	*line;

	fd = open("here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	while (1)
	{
		line = readline("heredoc> ");
		if (!ft_strncmp(line, tokens[*i + 1]->value,
			ft_strlen(tokens[*i + 1]->value)))
			break ;
		if (line && *line)
		{
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
	free(line);
	close(fd);
	return (new_cmd(ft_strdup("here_doc"), NULL, NULL, NULL));
}
