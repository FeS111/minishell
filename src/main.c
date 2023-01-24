
#include "../include/minishell.h"
#include <readline/readline.h>
#include <stdlib.h>


void	history(t_options *o)
{
	free_tokens(o->tokens);
	//free_table(o->table)
	o->tokens = NULL;
	if (o->line && *(o->line))
	{
		add_history(o->line);
		free(o->line);
		o->line = NULL;
	}
}

int	main(void)
{
	t_options		*o;
	t_parse_table	**table;
	int		j;

	o = create_options();
	signal(SIGINT, ctrl_c_handler);
	while (1)
	{
		o->line = readline("minishell> ");
		if (!o->line || !ft_strncmp(o->line, "exit", 4))
			panic(o, 0);
		lexer(o);
		j = 0;
		while (o->tokens[j])
		{
			ft_printf("%s %d\n", o->tokens[j]->value, o->tokens[j]->type);
			j++;
		}
		table = parser(o->tokens);
		if (table)
		{
			ft_printf("%s, %i, %i\n", table[0]->cmd[0], table[0]->in, table[0]->out);
			free_table(table);
		}
		history(o);
	}
	panic(o, 0);
}
