#include "../include/minishell.h"

char	**build_cmd(t_token **tokens, int *in, int *out, int *i)
{
	if (tokens[*i]->type == IO)
		return (handle_io(tokens, in, out, i));
	else if (tokens[*i]->type == IOR)
		return (handle_ior(tokens, in, out, i));
	else if (tokens[*i]->type == WORD)
		return (handle_word(tokens, in, out, i));
	return (NULL);
}

t_parse_table *new_table(char **cmd, int in, int out)
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

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cmd[i])
			free(cmd[i]);
		i++;
	}
}

void	free_table(t_parse_table **table)
{
	int	i;
	int j;

	i = 0;
	while (table[i])
	{
		j = 0;
		if (table[i]->cmd)
		{
			free_cmd(table[i]->cmd);
			free(table[i]->cmd);
		}
		if (table[i]->in > 2)
			close(table[i]->in);
		if (table[i]->out > 2)
			close(table[i]->out);
		free(table[i]);
		i++;
	}
	free(table);
}
