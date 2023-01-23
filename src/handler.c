#include "../include/parser.h"
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

void	panic_token(char *str)
{
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putendl_fd(str, 2);
}

char	**handle_io(t_token **tokens, int *in, int *out, int *i)
{
	char	**new;

	new = malloc(sizeof(char *)  + 1);
	new[1] = NULL;
	if (!ft_strncmp(tokens[*i]->value, "<", 1))
	{
		if (*i > 0)
			*out = open(tokens[*i - 1]->value, W_OK);
		else
			*out = 0;
		*i += 1;
		if (tokens[*i]->type != WORD)
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
	else if (ft_strncmp(tokens[*i]->value, ">", 1))
	{
		i++;
		if (tokens[*i]->type != WORD)
			return (panic_token(tokens[*i]->value), NULL);
		return (NULL);
	}
	else if (ft_strncmp(tokens[*i]->value, "<<", 2))
	{
		i++;
		if (tokens[*i]->type != WORD)
			return (panic_token(tokens[*i]->value), NULL);
		return (NULL);
	}
	else if (ft_strncmp(tokens[*i]->value, ">>", 2))
	{
		i++;
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
