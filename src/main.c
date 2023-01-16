
#include "../include/minishell.h"

int	main(void)
{
	char	*line;
	t_token	**tokens;
	int		i;
	int		j;

	ft_printf("\e[1;1H\e[2J");
	i = 0;
	while (1)
	{
		line = readline("minishell> ");
		if (!ft_strncmp(line, "exit", 4))
		{
			ft_putendl_fd("exit", 1);
			free(line);
			return (0);
		}
		tokens = lexer(line);
		i++;
		if (line && *line)
		{
			add_history(line);
			free(line);
		}
		j = 0;
		//while (tokens[j])
		//{
		//	ft_putendl_fd(tokens[j]->value, 1);
		//	j++;
		//}
	}
	return (0);
}
