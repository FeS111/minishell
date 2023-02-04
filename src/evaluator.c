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
		newValue = ft_getenv(go, tmp);
	free(tmp);
	if (!newValue)
		newValue = ft_strdup("");
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
	while (!is_whitespace(str[i]) && !ft_strchr("\"'\0", str[i]))
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

static char	*remove_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			str = str_remove_char(str, str[i]);
			break ;
		}
	}
	return(str);
}

void	evaluator(t_options *o)
{
	int	i;
	int	j;
	int	k;
	int	replace;
	int	double_quotes;

	replace = 1;
	double_quotes = 0;
	i = -1;
	while (o->tables[++i])
	{
		k = -1;
		while (o->tables[i]->cmd->args && o->tables[i]->cmd->args[++k])
		{
			j = -1;
			while (o->tables[i]->cmd->args[k] && o->tables[i]->cmd->args[k][++j] != '\0')
			{
				if (o->tables[i]->cmd->args[k][j] == '"' && !double_quotes && replace)
					double_quotes = 1;
				else if (o->tables[i]->cmd->args[k][j] == '\'' && replace && !double_quotes)
					replace = 0;
				else if (o->tables[i]->cmd->args[k][j] == '\'' && !replace && !double_quotes)
					replace = 1;
				if (!replace)
					continue ;
				if (o->tables[i]->cmd->args[k][j] == '$')
					o->tables[i]->cmd->args[k] = replace_variable(o, o->tables[i]->cmd->args[k], j, get_varlength(&o->tables[i]->cmd->args[k][j]));
				else if (o->tables[i]->cmd->args[k][j] == '~')
					o->tables[i]->cmd->args[k] = replace_home(o->tables[i]->cmd->args[k], j);
			}
			o->tables[i]->cmd->args[k] = remove_quotes(o->tables[i]->cmd->args[k]);
		}
		k = -1;
		replace = 1;
		while (o->tables[i]->cmd->cmd[++k] != '\0')
		{
			if (o->tables[i]->cmd->cmd[k] == '\'' && replace)
				replace = 0;
			else if (o->tables[i]->cmd->cmd[k] == '\'' && !replace)
				replace = 1;
			if (!replace)
				continue ;
			if (o->tables[i]->cmd->cmd[k] == '$')
				o->tables[i]->cmd->cmd = replace_variable(o, o->tables[i]->cmd->cmd, k, get_varlength(&o->tables[i]->cmd->cmd[k]));
			else if (o->tables[i]->cmd->cmd[k] == '~')
				o->tables[i]->cmd->cmd = replace_home(o->tables[i]->cmd->cmd, k);
		}
		o->tables[i]->cmd->cmd = remove_quotes(o->tables[i]->cmd->cmd);
	}
}
