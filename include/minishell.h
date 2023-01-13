
#ifndef MINISHELL_H
# define MINISHELL_H

# include "./buildin.h"
# include "./lexer.h"

# ifndef LIBFT_H
#  include "../libft/libft.h"
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdio.h>

# include <readline/history.h>
# include <readline/readline.h>

t_token		**lexer(char *line);

char		**split_join(char **str);

char		*strjoinn(char **arr, char *c, int start, int end);

size_t		getnext_whitespace(char *str);

#endif
