#include "../include/minishell.h"

char	**handle_io(t_token **tokens, int *in, int *out, int *i)
{
	if (!ft_strncmp(tokens[*i]->value, "<", 1))
	{
		if (tokens[*i + 1]->type != WORD)
			return (panic_token(tokens[*i]->value), NULL);
		return (left_redir(tokens, in, out, i));
	}
	else if (!ft_strncmp(tokens[*i]->value, ">", 1))
		return (right_redir(tokens, in, out, i));
	else if (!ft_strncmp(tokens[*i]->value, "<<", 2))
	{
		*i += 1;
		if (tokens[*i]->type != WORD)
			return (panic_token(tokens[*i]->value), NULL);
		return (NULL);
	}
	else if (!ft_strncmp(tokens[*i]->value, ">>", 2))
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
	char	**new;
	char	*word;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	if (tokens[*i - 1] && tokens[*i - 1])
		*in = PIPE_FD;
	if (tokens[*i + 1] && tokens[*i + 1]->type == IO)
	{
		if (!ft_strncmp(tokens[*i + 1]->value, ">", 1))
		{
			*out = WRITE;
			new = new_cmd(ft_strdup(tokens[*i]->value), NULL, NULL, NULL);
			*i += 1;
			return (new);
		}
		else if (!ft_strncmp(tokens[*i + 1]->value, ">>", 2))
		{
			*out = WRITE;
			new = new_cmd(ft_strdup(tokens[*i]->value), NULL, NULL,
							ft_strdup(tokens[*i + 1]->value));
			*i += 1;
			return (new);
		}
		else
		{
			new = new_cmd(ft_strdup(tokens[*i]->value), NULL, NULL, NULL);
			*i += 1;
			return (new);
		}
	}
	else
	{
		word = ft_strdup(tokens[*i]->value);
		*i += 1;
		while (tokens[*i])
		{
			if (tokens[*i] && tokens[*i]->type == OPTION)
			{
				if (tmp)
					tmp = ft_strjoin_gnl(tmp, " ");
				tmp = ft_strjoin_gnl(tmp, tokens[*i]->value);
			}
			else if (tokens[*i] && tokens[*i]->type == OPTION2)
			{
				if (tmp2)
					tmp2 = ft_strjoin_gnl(tmp2, tokens[*i]->value);
				tmp2 = ft_strjoin_gnl(tmp2, " ");
			}
			else if (tokens[*i] && tokens[*i]->type == WORD)
			{
				if (tmp3)
					tmp3 = ft_strjoin_gnl(tmp3, tokens[*i]->value);
				tmp3 = ft_strjoin_gnl(tmp3, " ");
			}
			*i += 1;
			if (tokens[*i] && !is_woo2(tokens[*i]->type))
				break;
		}
		new = new_cmd(word, tmp, tmp2 ,tmp3);
		if (tokens[*i] && tokens[*i]->type == PIPE)
			*out = PIPE_FD;
		else
			*out = STD_OUTPUT;
		return (new);
	}
	return (NULL);
}
