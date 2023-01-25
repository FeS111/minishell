#include "../include/minishell.h"

char	*replace_join(char *one, char *two)
{
	char	*res;

	res = ft_strjoin_gnl(one, two);
	free(two);
	return (res);
}

char		*str_replace(t_replace_options o)
{
	int		i;
	char	*res;

	i = o.start - 1;
	while (o.str[++i] != '\0' && i < o.end)
	{
		if (o.str[i] != '$')
			continue ;
		res = ft_substr(o.str, 0, i);
		res = ft_strjoin_gnl(res, o.newValue);
		res = replace_join(res, ft_substr(o.str, o.end, ft_strlen(o.str) - o.end));
	}
	return (res);
}
