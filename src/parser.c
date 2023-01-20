#include "../include/parser.h"
#include <stdlib.h>

t_parse_table	**parser(t_token **tokens)
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
	tables = malloc(sizeof(t_parse_table *) * token_size(tokens));
	while (tokens[i])
	{
		tables[j] = new_table(build_cmd(tokens, &in, &out, &i), in, out);
		if (!tables[j])
			exit(EXIT_FAILURE);
		j++;
		i++;
	}
	return (tables);
}
