
#include "../include/minishell.h"

int	main(void)
{
	char	*line;
	t_token	*tokens;
	int		i;

	i = 0;
	while (1)
	{
		line = readline("minishell> ");
		if (line && *line)
			add_history(line);
		if (!ft_strncmp(line, "exit", 4))
		{
			ft_putendl_fd("exit", 1);
			free(line);
			return (0);
		}
		tokens = lexer(line);
		i++;
		free(line);
	}
	return (0);
}
