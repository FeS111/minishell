#include "../include/parser.h"

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
	new = malloc(sizeof(t_parse_table *));
	new->cmd = cmd;
	new->in = in;
	new->out = out;
	return (new);
}
