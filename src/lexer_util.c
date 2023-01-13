/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luntiet- <luntiet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:42:49 by fschmid           #+#    #+#             */
/*   Updated: 2023/01/13 17:17:37 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

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

char	*get_quoted(char *str)
{
	int		end;

	end = 1;
	if (str[0] == '\'')
		while (str[end] != '\'' || (str[end] == '\'' && str[end - 1] == '\\'))
			end++;
	else
		while (str[end] != '\"' || (str[end] == '\"' && str[end - 1] == '\\'))
			end++;
	return (ft_substr(str, 0, end + 1));
}
