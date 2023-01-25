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

void	evaluator(t_options *o, t_parse_table **cmds)
{
	int	i;
	int	j;
	int	replace;

	replace = 1;
	i = -1;
	while (cmds[++i])
	{
		j = -1;
		while (cmds[i]->cmd[ARGS][++j] != '\0')
		{
			if (cmds[i]->cmd[ARGS][j] == '\'' && replace)
				replace = 0;
			if (cmds[i]->cmd[ARGS][j] == '\'' && !replace)
				replace = 1;
			if (!replace)
				continue ;
			if (cmds[i]->cmd[ARGS][j] == '$')
				cmds[i]->cmd[ARGS] = replace_variable(o, cmds[i]->cmd[ARGS], j, getnext_whitespace(&cmds[i]->cmd[ARGS][j]));
			else if (cmds[i]->cmd[ARGS][j] == '~')
				cmds[i]->cmd[ARGS] = replace_home(cmds[i]->cmd[ARGS], j);
		}
	}
}
