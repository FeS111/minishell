
#include "../include/minishell.h"

t_token	*get_token(char *charset)
{
	int	i;

	i = 0;
	if (charset[0] == ' ')
		i++;
	if (ft_strchr("\n\0", charset[0]))
		return (NULL);
	else if (charset[0] == '\'' || charset[0] == '\"')
		return (get_quoted(charset));
	else if (charset[0] == '-')
		return (get_option(charset));
	else if (ft_strchr("><#", charset[0]))
		return (get_io(charset));
	else if (charset[0] == '&')
		return (get_ampersand(charset));
	else if (charset[0] == '|')
		return (get_pipe(charset));
	else if (charset[0] == '$')
		return (get_variable(charset));
	else
	{
		while (!is_whitespace(charset[i]))
			i++;
		if (is_word(charset, i))
			return (new_token(ft_substr(charset, 0, i), WORD));
	}
	return (NULL);
}

void	lexer(t_options *o)
{
	t_token	**tokens;
	int		i;
	int		j;

	if (!o->line)
		return ;
	i = 0;
	j = 0;
	tokens = malloc(sizeof(t_token *) * 1024);
	ft_bzero(tokens, 1024);
	while (o->line[i])
	{
		tokens[j] = get_token(&(o->line)[i]);
		if (tokens[j])
		{
			i += ft_strlen(tokens[j]->value);
			j++;
			continue;
		}
		i++;
	}
	o->tokens = tokens;
}
