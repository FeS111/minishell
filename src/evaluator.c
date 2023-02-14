/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:55:34 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/14 10:17:30 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern t_global	g_global;

char	*replace_variable(t_options *go, char *str, int start, int end)
{
	t_replace_options	o;
	char				*new_value;
	char				*tmp;

	tmp = ft_substr(str, start + 1, end - 1);
	if (str[start + 1] == '?')
		new_value = ft_itoa(g_global.status);
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

char	*remove_quotes(char *str)
{
	int		i;
	char	*trim;

	i = -1;
	trim = NULL;
	if (str[0] == '"' || str[0] == '\'')
	{
		trim = strtrim_one(str, "\'\"");
		trim = str_remove_char(trim, '\\');
		return (trim);
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
