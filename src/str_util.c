#include "../include/minishell.h"
#include <stdio.h>

char	*replace_join(char *one, char *two)
{
	char	*res;

	res = ft_strjoin_gnl(one, two);
	free(two);
	return (res);
}

char	*str_replace(t_replace_options o)
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
		res = replace_join(res,
				ft_substr(o.str, o.end, ft_strlen(o.str) - o.end));
	}
	free(o.str);
	free(o.newValue);
	return (res);
}

char	**split_first(char *str, char c)
{
	char	**res;
	int		pos;

	if (!ft_strchr(str, c))
		return (NULL);
	res = malloc(sizeof(char *) * 3);
	res[2] = NULL;
	pos = ft_strchr(str, c) - str;
	res[0] = ft_substr(str, 0, pos);
	res[1] = ft_substr(str, pos + 1, ft_strlen(str) - 1);
	return  (res);
}

char	*str_remove_char(char *str, char c)
{
	int		i;
	int		j;
	char	*res;

	i = -1;
	j = -1;
	res = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	while (str[++i] != '\0')
	{
		if (str[i] != c)
			res[++j] = str[i];
	}
	free(str);
	return (res);
}
