/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:42:49 by fschmid           #+#    #+#             */
/*   Updated: 2023/01/13 17:05:49 by fschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

int	is_word(char *str, int end)
{
	int	i;

	i = -1;
	while (str[++i] != '\0' && i < end)
	{
		if (str[i] == '\\' && str[i + 1] != '\0' && (i + 1) < end
			&& ft_strchr("%=+’”()$/_-.\?*~\"", str[i + 1]))
		{
			++i;
			continue ;
		}
		return (0);
		if (ft_strchr("=”()/_-.~]+", str[i]) || ft_isalnum(str[i]))
			continue ;
	}
	return (1);
}

char	*is_quoted(char *str, int i)
{
	int		start;

	start = i;
	if (str[i] == '\'')
		while (str[i] != '\'')
			i++;
	else
		while (str[i] != '\"')
			i++;
	return (ft_substr(str, start, i));
}

t_token	*get_option(char *str)
{
	return (new_token(ft_substr(str, 0, getnext_whitespace(str)), OPTION));
}
