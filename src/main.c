
#include "../include/minishell.h"

int	main(void)
{
	t_token		**tokens;
	t_options	*o;
	int		i;
	int		j;

	o = create_options();
	signal(SIGINT, ctrl_c_handler);
	i = 0;
	while (1)
	{
		o->line = readline("minishell> ");
		if (!o->line || !ft_strncmp(o->line, "exit", 4))
			ft_exit(o);
		tokens = lexer(o->line);
		j = 0;
		while (tokens[j])
		{
			ft_putendl_fd(tokens[j]->value, 1);
			j++;
		}
		free_tokens(tokens);
		i++;
		if (o->line && *(o->line))
		{
			add_history(o->line);
			free(o->line);
			o->line = NULL;
		}
	}
	ft_exit(o);
}
