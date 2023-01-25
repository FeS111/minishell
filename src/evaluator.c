#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

char	*replace_variable(char *str, int start, int end)
{
	t_replace_options	o;
	char				*newValue;
	char				*tmp;

	tmp = ft_substr(str, start + 1, end - 1);
	newValue = getenv(tmp);
	free(tmp);
	if (!newValue)
		return str;
	o.str = ft_strdup(str);
	o.start = start;
	o.end = start + end - 1;
	o.old = ft_substr(str, start, end);
	o.newValue = newValue;
	free(str);
	free(o.old);
	return (str_replace(o));
}

void	evaluator(t_parse_table **cmds)
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
				cmds[i]->cmd[ARGS] = replace_variable(cmds[i]->cmd[ARGS], j, getnext_whitespace(&cmds[i]->cmd[ARGS][j]));
		}
	}
}
