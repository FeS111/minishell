#include "../include/minishell.h"
#include <stdlib.h>

t_parse_cmd	*build_cmd(t_options *o, int *in, int *out, int *i)
{
	if (o->tokens[*i]->type == IO)
		return (handle_io(o, in, out, i));
	else if (o->tokens[*i]->type == WORD)
		return (handle_word(o->tokens, in, out, i));
	return (NULL);
}

t_parse_table *new_table(t_parse_cmd *cmd, int in, int out)
{
	t_parse_table *new;

	if (!cmd)
		return (NULL);
	new = malloc(sizeof(t_parse_table));
	new->cmd = cmd;
	new->in = in;
	new->out = out;
	return (new);
}

void	free_cmd(t_parse_cmd *cmd)
{
	free(cmd->cmd);
	free(cmd->opt);
	free(cmd->opt2);
	split_free(cmd->args);
	free(cmd);
}

void	free_table(t_parse_table **table)
{
	int	i;
	int j;

	i = 0;
	if (!table)
		return ;
	while (table[i])
	{
		j = 0;
		if (table[i]->cmd)
			free_cmd(table[i]->cmd);
		if (table[i]->in > 2)
			close(table[i]->in);
		if (table[i]->out > 2)
			close(table[i]->out);
		free(table[i]);
		i++;
	}
	free(table);
}
