#include "../include/minishell.h"

size_t	getnext_whitespace(char *str)
{
	size_t	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (ft_strchr(" \t\r\v\f", str[i]))
			return (i);
	}
	return (0);
}
