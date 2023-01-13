

#include "../include/minishell.h"

t_token	*new_token(char *args, enum e_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = args;
	new->type = type;
	return (new);
}
