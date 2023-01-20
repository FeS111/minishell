#include "../include/parser.h"

void	panic_return(char *str)
{
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putendl_fd(str, 2);
}

char	**handle_io(t_token **tokens, int *in, int *out, int *i)
{
	if (ft_strncmp(tokens[*i]->value, "<", 1))
	{
		i++;
		if (tokens[*i]->type != WORD)
			return (panic_return(tokens[*i]->value), NULL);
		return (NULL);
	}
	else if (ft_strncmp(tokens[*i]->value, ">", 1))
	{
		i++;
		if (tokens[*i]->type != WORD)
			return (panic_return(tokens[*i]->value), NULL);
		return (NULL);
	}
	else if (ft_strncmp(tokens[*i]->value, "<<", 2))
	{
		i++;
		if (tokens[*i]->type != WORD)
			return (panic_return(tokens[*i]->value), NULL);
		return (NULL);
	}
	else if (ft_strncmp(tokens[*i]->value, ">>", 2))
	{
		i++;
		if (tokens[*i]->type != WORD)
			return (panic_return(tokens[*i]->value), NULL);
		return (NULL);
	}
	else
		return (NULL);
}

char	**handle_ior(t_token **tokens, int *in, int *out, int *i)
{
	return (NULL);
}

char	**handle_word(t_token **tokens, int *in, int *out, int *i)
{
	return (NULL);	
}
