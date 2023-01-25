#include "../include/minishell.h"

char	**left_redir(t_token **tokens, int *in, int *out, int *i)
{
	char **new;

	if (*i > 0)
		*out = WRITE;
	else
		*out = STD_OUTPUT;
	*i += 1;
	if (!tokens[*i] || tokens[*i]->type != WORD)
		return (panic_token(tokens[*i]->value), NULL);
	*in = READ;
	if (*in < 0)
	{
		perror(tokens[*i]->value);
		*in = STD_INPUT;
		i++;
		return (NULL);
	}
	new = new_cmd(ft_strdup(tokens[*i]->value), NULL, NULL, NULL);
	return (new);
}

char	**right_redir(t_token **tokens, int *in, int *out, int *i)
{
	char	**new;

	if (tokens[*i + 1])
	{
		*i += 1;
		*out = WRITE;
		*in = STD_INPUT;
		new = new_cmd(ft_strdup(tokens[*i]->value), NULL, NULL, NULL);
		return (new);
	}
	else
		return (ft_putendl_fd("parse error near \\n \n", 2), NULL);
	return (NULL);
}
