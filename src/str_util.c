#include "../include/minishell.h"
#include <stddef.h>

char	*str_replace(char *str, char *old, char *newValue)
{
	size_t	start;
	char	*res;
	char	*tmp;
	char	*tmp2;

	tmp2 = str;
	res = NULL;
	while (ft_strnstr(tmp2, old, ft_strlen(tmp2)))
	{
		free(res);
		start = (size_t)(ft_strnstr(tmp2, old, ft_strlen(tmp2)) - tmp2);
		res = ft_substr(tmp2, 0, start);
		res = ft_strjoin_gnl(res, newValue);
		start += ft_strlen(old);
		tmp = ft_substr(tmp2, start, ft_strlen(tmp2) - start);
		res = ft_strjoin_gnl(res, tmp);
		free(tmp2);
		free(tmp);
		tmp2 = ft_strdup(res);
	}
	return (res);
}
