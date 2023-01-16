
# include "../include/minishell.h"

int	is_word(char *str, int end)
{
	int	i;

	i = -1;
	while (str[++i] != '\0' && i < end)
	{
		if (str[i] == '\\' && str[i + 1] != '\0' && (i + 1) < end
			&& ft_strchr("%=+’”()$/_-.\?*~\"", str[i + 1]))
		{
			++i;
			continue ;
		}
		return (0);
		if (ft_strchr("=”()/_-.~]+", str[i]) || ft_isalnum(str[i]))
			continue ;
	}
	return (1);
}

char	*get_quoted(char *str)
{
	int		end;

	end = 1;
	if (str[0] == '\'')
		while (str[end] != '\'' || (str[end] == '\'' && str[end - 1] == '\\'))
			end++;
	else
		while (str[end] != '\"' || (str[end] == '\"' && str[end - 1] == '\\'))
			end++;
	return (ft_substr(str, 0, end + 1));
}

t_token	*get_option(char *str)
{
	if (ft_strchr(str, '='))
		return (new_token(ft_substr(str, 0, getnext_whitespace(str)), OPTION2));
	return (new_token(ft_substr(str, 0, getnext_whitespace(str)), OPTION));
}
