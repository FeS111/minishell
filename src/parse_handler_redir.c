#include "../include/minishell.h"
#include <stdio.h>

t_parse_cmd	*left_redir(t_token **tokens, int *in, int *out, int *i)
{
	if (*i > 0)
		*out = WRITE;
	else
		*out = STD_OUTPUT;
	*i += 1;
	*in = READ;
	if (*in < 0)
	{
		perror(tokens[*i]->value);
		*in = STD_INPUT;
		return (NULL);
	}
	return (new_cmd(ft_strdup(tokens[*i]->value), NULL, NULL, NULL));
}

t_parse_cmd	*right_redir(t_token **tokens, int *in, int *out, int *i)
{

	if (tokens[*i + 1])
	{
		*i += 1;
		*out = WRITE;
		*in = STD_INPUT;
		return (new_cmd(ft_strdup(tokens[*i]->value), NULL, NULL, NULL));
	}
	else
		return (panic_token("`newline'"), NULL);
	return (NULL);
}
