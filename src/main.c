
#include "../include/minishell.h"

int	main(void)
{
	t_token		**tokens;
	t_options	*o;
	int		j;

	o = create_options();
	signal(SIGINT, ctrl_c_handler);
	while (1)
	{
		o->line = readline("minishell> ");
		if (!o->line || !ft_strncmp(o->line, "exit", 4))
			panic(o);
		tokens = lexer(o->line);
		j = 0;
		while (tokens[j])
		{
			ft_putendl_fd(tokens[j]->value, 1);
			j++;
		}
		free_tokens(tokens);
		if (o->line && *(o->line))
		{
			add_history(o->line);
			free(o->line);
			o->line = NULL;
		}
	}
	panic(o);
}
