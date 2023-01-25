#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

char	*replace_variable(t_options *go, char *str, int start, int end)
{
	t_replace_options	o;
	char				*newValue;
	char				*tmp;

	tmp = ft_substr(str, start + 1, end - 1);
	if (str[start + 1] == '?')
		newValue = ft_itoa(go->last_status);
	else
		newValue = getenv(tmp);
	free(tmp);
	if (!newValue)
		return str;
	o.str = ft_strdup(str);
	o.start = start;
	o.end = start + end;
	o.old = ft_substr(str, start, end);
	o.newValue = newValue;
	free(str);
	free(o.old);
	return (str_replace(o));
}

static int	get_varlength(char *str)
{
	int	i;

	i = 0;
	while (!is_whitespace(str[i]) && ! ft_strchr("\"\0", str[i]))
		i++;
	return (i);
}

char	*replace_home(char *str, int start)
{
	char	*home;
	char	*res;

	home = getenv("HOME");
	if (start > 0)
		res = ft_substr(str, 0, start);
	else
		res = ft_strdup("");
	res = ft_strjoin_gnl(res, home);
	res = replace_join(res, ft_substr(str, start + 1, ft_strlen(str) - start));
	free(str);
	return (res);
}

void	evaluator(t_options *o)
{
	int	i;
	int	j;
	int	replace;

	replace = 1;
	i = -1;
	while (o->tables[++i])
	{
		j = -1;
		while (o->tables[i]->cmd[ARGS][++j] != '\0')
		{
			if (o->tables[i]->cmd[ARGS][j] == '\'' && replace)
				replace = 0;
			if (o->tables[i]->cmd[ARGS][j] == '\'' && !replace)
				replace = 1;
			if (!replace)
				continue ;
			if (o->tables[i]->cmd[ARGS][j] == '$')
				o->tables[i]->cmd[ARGS] = replace_variable(o, o->tables[i]->cmd[ARGS], j, get_varlength(&o->tables[i]->cmd[ARGS][j]));
			else if (o->tables[i]->cmd[ARGS][j] == '~')
				o->tables[i]->cmd[ARGS] = replace_home(o->tables[i]->cmd[ARGS], j);
		}
	}
}
