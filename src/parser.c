#include "../include/minishell.h"

void	parser(t_options *o)
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
	tables = malloc(sizeof(t_parse_table *) * token_size(o->tokens) + 1);
	while (o->tokens[i])
	{
		tables[j] = new_table(build_cmd(o->tokens, &in, &out, &i), in, out);
		if (!tables[j])
			break;
 		j++;
		i++;
	}
	tables[j] = NULL;
	o->tables = tables;
}
