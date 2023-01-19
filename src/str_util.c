#include "../include/minishell.h"
#include <stddef.h>

char	*str_replace(char *str, char *old, char *newValue)
{
	size_t	start;
	char	*res;
	char	*tmp;

	start = (size_t)(ft_strnstr(str, old, ft_strlen(str)) - str);
	res = ft_substr(str, 0, start);
	res = ft_strjoin_gnl(res, newValue);
	start += ft_strlen(old);
	tmp = ft_substr(str, start, ft_strlen(str) - start);
	res = ft_strjoin_gnl(res, tmp);
	free(str);
	free(tmp);
	return (res);
}
