
#include "../include/minishell.h"
#include <readline/readline.h>
#include <stdlib.h>


void	history(t_options *o)
{
	free_tokens(o->tokens);
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
	t_options	*o;
	int		j;
	t_parse_table	**cmds;
	char			**cmd = ft_calloc(sizeof(char *),  5);
	char			**cmd2 = ft_calloc(sizeof(char *),  5);
	cmd[0] = ft_strdup("/bin/ls");
	cmd[1] = ft_strdup("-lah");
	cmd2[0] = ft_strdup("wc");
	cmd2[1] = ft_strdup("-l");

	cmds = malloc(sizeof(t_parse_table *) * 3);
	cmds[0] = new_table(cmd, 0, -2);
	cmds[1] = new_table(cmd2, 0, 1);
	cmds[2] = NULL;


	o = create_options();
	executer(o, cmds);
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
		history(o);
	}
	panic(o, 0);
}
