#include "../include/minishell.h"

char	**parser(t_token **tokens)
{
	int 			i;
	char			**table;
	t_parse_table	**tables;

	i = 0;
	table = malloc((sizeof(char *) * 4) + 1);
	table[4] = NULL;
	tables = NULL;
	while (tokens[i])
	{
		i++;
	}
}
