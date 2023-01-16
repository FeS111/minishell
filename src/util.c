#include "../include/minishell.h"

size_t	getnext_whitespace(char *str)
{
	size_t	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (is_whitespace(str[i + 1]) || str[i + 1] == '\0')
			return (i + 1);
	}
	return (0);
}

int	is_whitespace(char c)
{
	if (ft_strchr(" \t\r\v\f\n", c))
		return (1);
	return (0);
}
