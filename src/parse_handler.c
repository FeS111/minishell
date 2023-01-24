#include "../include/parser.h"

char	**handle_io(t_token **tokens, int *in, int *out, int *i)
{
	if (!ft_strncmp(tokens[*i]->value, "<", 1))
	{
		if (tokens[*i + 1]->type != WORD)
			return (panic_token(tokens[*i]->value), NULL);
		return (left_redir(tokens, in, out, i));
	}
	else if (ft_strncmp(tokens[*i]->value, ">", 1))
		return (right_redir(tokens, in, out, i));
	else if (ft_strncmp(tokens[*i]->value, "<<", 2))
	{
		*i += 1;
		if (tokens[*i]->type != WORD)
			return (panic_token(tokens[*i]->value), NULL);
		return (NULL);
	}
	else if (ft_strncmp(tokens[*i]->value, ">>", 2))
	{
		*i += 1;
		if (tokens[*i]->type != WORD)
			return (panic_token(tokens[*i]->value), NULL);
		return (NULL);
	}
	return (NULL);
}

char	**handle_ior(t_token **tokens, int *in, int *out, int *i)
{
	tokens = NULL;
	in = out;
	*i = *i;
	return (NULL);
}

char	**handle_word(t_token **tokens, int *in, int *out, int *i)
{
	if (tokens[*i + 1] && tokens[*i + 1]->type == IO)
	{
		*i += 1;
		return (handle_io(tokens, in, out, i));
	}
	return (NULL);
}
