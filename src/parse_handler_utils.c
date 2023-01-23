#include "../include/parser.h"

char	**left_redir(t_token	**tokens, int *in, int *out, int *i)
{
	char **new;

	new = malloc(sizeof(char *) + 1);
	new[1] = NULL;
	if (*i > 0)
		*out = open(tokens[*i - 1]->value, W_OK);
	else
		*out = 0;
	*i += 1;
	if (!tokens[*i] || tokens[*i]->type != WORD)
		return (panic_token(tokens[*i]->value), NULL);
	*in = open(tokens[*i]->value, O_RDONLY);
	if (*in < 0)
	{
		perror(tokens[*i]->value);
		*in = 0;
		i++;
		return (NULL);
	}
	new[0] = ft_strdup(tokens[*i]->value);
	return (new);
}
