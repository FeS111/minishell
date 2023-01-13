/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:17:52 by fschmid           #+#    #+#             */
/*   Updated: 2023/01/13 11:48:41 by fschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./buildin.h"
# include "./lexer.h"
# include "../libft/libft.h"

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdio.h>

# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_token
{
	char	*cmd;
	char	**args;
}	t_token;

t_token		*parse_input(char *line);

char		**split_join(char **str);

t_token		new_token(char **cmd);

char	*strjoinn(char **arr, char *c, int start, int end);

#endif
