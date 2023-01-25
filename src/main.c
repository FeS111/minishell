
#include "../include/minishell.h"

void	history(t_options *o)
{
	free_tokens(o->tokens);
	free_table(o->tables);
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
	int				j;

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
		parser(o);
		if (o->tables)
		{
			j = 0;
			while (o->tables[j])
			{
				ft_printf("%s, %s, %s, %s, %i, %i\n", o->tables[j]->cmd[CMD], o->tables[j]->cmd[OPT], o->tables[j]->cmd[OPT2], o->tables[j]->cmd[ARGS], o->tables[j]->in, o->tables[j]->out);
				j++;
			}
		}
		evaluator(o);
		j = 0;
		while (o->tables[j])
		{
			ft_printf("%s, %s, %s, %s, %i, %i\n", o->tables[j]->cmd[CMD], o->tables[j]->cmd[OPT], o->tables[j]->cmd[OPT2], o->tables[j]->cmd[ARGS], o->tables[j]->in, o->tables[j]->out);
			j++;
		}
		history(o);
	}
	panic(o, 0);
}
