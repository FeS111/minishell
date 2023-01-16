#include "../include/minishell.h"

t_token *get_quoted(char *str)
{
	int		end;

	end = 1;
	if (str[0] == '\'')
		while (str[end] != '\'' || (str[end] == '\'' && str[end - 1] == '\\'))
			end++;
	else
		while (str[end] != '\"' || (str[end] == '\"' && str[end - 1] == '\\'))
			end++;
	return (new_token(ft_substr(str, 0, end + 1), IO));
}

t_token	*get_option(char *str)
{
	if (ft_strchr(str, '='))
		return (new_token(ft_substr(str, 0, getnext_whitespace(str)), OPTION2));
	return (new_token(ft_substr(str, 0, getnext_whitespace(str)), OPTION));
}

t_token	*get_io(char *str)
{
	if (ft_strchr("<>#", str[0]))
	{
		if (str[1] == str[0])
			return (new_token(ft_substr(str, 0, 2), IO));
		else if (is_whitespace(str[1]))
			return (new_token(ft_substr(str, 0, 1), IO));
		else if (str[1] == '&')
			return (new_token(ft_substr(str, 0, 2), IOR));
	}
	return (NULL);
}

t_token	*get_pipe(char *str)
{
	if (str[0] == '|')
		return (new_token(ft_substr(str, 0, 1), PIPE));
	return (NULL);
}

t_token	*get_ampersand(char *str)
{
	if (str[0] == '&')
		return (new_token(ft_strdup("&"), AMBERSAND));
	if (str[0] == '&' && str[1] == '&')
		return (new_token(ft_strdup("&&"), AMBERSAND));
	return (NULL);
}
