
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
	else
	{
		while (!is_whitespace(charset[i]))
			i++;
		if (is_word(charset, i))
			return (new_token(ft_substr(charset, 0, i), WORD));
	}
	return (NULL);
}

t_token	**lexer(char *line)
{
	t_token	**tokens;
	int		i;
	int		j;

	if (!line)
		return (NULL);
	i = 0;
	j = 0;
	tokens = malloc(sizeof(t_token *));
	while (line[i])
	{
		tokens[j] = get_token(&line[i]);
		if (tokens[j])
		{
			ft_putendl_fd(tokens[j]->value, 1);
			i += ft_strlen(tokens[j]->value);
			j++;
			continue;
		}
		i++;
	}
	tokens[j] = NULL;
	return (tokens);
}
