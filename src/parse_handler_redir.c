#include "../include/parser.h"

char	**left_redir(t_token **tokens, int *in, int *out, int *i)
{
	char **new;

	new = malloc(sizeof(char *) + 1);
	new[1] = NULL;
	if (*i > 0)
		*out = WRITE;
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

char	**right_redir(t_token **tokens, int *in, int *out, int *i)
{
	char	**new;

	new = malloc(sizeof(char *) * 3 + 1);
	new[3] = NULL;
	if (*i == 0)
	{
		if (tokens[*i + 1])
		{
			*i += 1;
			*out = open(tokens[*i]->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			*in = 1;
			new[0] = ft_strdup(tokens[*i]->value);
			return (new);
		}
		else
			return (ft_putendl_fd("parse error near \\n \n", 2), NULL);
	}
	return (NULL);
}
