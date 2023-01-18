
#include "../include/minishell.h"

int	main(void)
{
	char		*line;
	t_token		**tokens;
	t_options	*o;
	int		i;
	int		j;

	o = create_options();
	ft_printf("\e[1;1H\e[2J");
	signal(SIGINT, ctrl_c_handler);

	i = 0;
	while (1)
	{
		line = readline("minishell> ");
		if (!line || !ft_strncmp(line, "exit", 4))
		{
			ft_putendl_fd("exit", 1);
			if (line)
				free(line);
			return (free_options(o), 0);
		}
		tokens = lexer(line);
		while (tokens[j])
		{
			ft_putendl_fd(tokens[j]->value, 1);
			j++;
		}
		free_tokens(tokens);
		i++;
		if (line && *line)
		{
			add_history(line);
			free(line);
		}
		j = 0;
	}
	system("leaks minishell");
	return (free_options(o), 0);
}
