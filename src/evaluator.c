#include "../include/minishell.h"

char	*replace_variable(t_options *go, char *str, int start, int end)
{
	t_replace_options	o;
	char				*new_value;
	char				*tmp;

	tmp = ft_substr(str, start + 1, end - 1);
	if (str[start + 1] == '?')
		new_value = ft_itoa(go->last_status);
	else
		new_value = ft_getenv(go, tmp);
	free(tmp);
	if (!new_value)
		new_value = ft_strdup("");
	o.str = ft_strdup(str);
	o.start = start;
	o.end = start + end;
	o.old = ft_substr(str, start, end);
	o.new_value = new_value;
	free(str);
	free(o.old);
	return (str_replace(o));
}

int	get_varlength(char *str)
{
	int	i;

	i = 0;
	while (!is_whitespace(str[i]) && !ft_strchr("\"='\0", str[i]))
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

char	*remove_quotes(char *str)
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
	return (str);
}

void	evaluator(t_options *o)
{
	int	i;
	int	replace;
	int	double_quotes;

	replace = 1;
	double_quotes = 0;
	i = -1;
	while (o->tables[++i])
	{
		evaluator_args(o, i);
		evaluator_cmd(o, i);
	}
}
