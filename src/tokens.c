

#include "../include/minishell.h"

t_token	*new_token(char *args, enum e_token_type type)
{
	t_token	*new;

	if (!args || !*args)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = args;
	new->type = type;
	return (new);
}

void	free_tokens(t_token **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]->value);
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
