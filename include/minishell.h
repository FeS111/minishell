/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luntiet- <luntiet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:17:52 by fschmid           #+#    #+#             */
/*   Updated: 2023/01/13 11:56:21 by luntiet-         ###   ########.fr       */
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


t_token		*lexer(char *line);

char		**split_join(char **str);


char	*strjoinn(char **arr, char *c, int start, int end);

#endif
