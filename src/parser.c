#include "../include/minishell.h"

int	count_pipes(t_token **tokens)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == PIPE)
			count++;
		i++;
	}
	return (count);
}

int	parser(t_options *o)
{
	int 			i;
	int				j;
	t_parse_table	**tables;
	int				in;
	int				out;

	i = 0;
	j = 0;
	in = 0;
	out = 1;
	tables = ft_calloc(sizeof(t_parse_table *), token_size(o->tokens) + 1);
	o->pipes = count_pipes(o->tokens);
	while (o->tokens[i])
	{
		tables[j] = new_table(build_cmd(o->tokens, &in, &out, &i), in, out);
		if (!tables[j])
			return (-1);
		j++;
		i++;
	}
	tables[j] = NULL;
	o->tables = tables;
	return (0);
}
