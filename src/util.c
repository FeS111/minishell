#include "../include/minishell.h"

size_t	getnext_whitespace(char *str)
{
	size_t	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (is_whitespace(str[i]))
			return (i);
	}
	return (0);
}

int	is_whitespace(char c)
{
	if (ft_strchr(" \t\r\v\f", c))
		return (1);
	return (0);
}
