
#ifndef MINISHELL_H
# define MINISHELL_H

# include "./buildin.h"
# include "./lexer.h"
# include "./executer.h"

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

typedef struct s_options
{
	char	**env;
	char	*pwd;
	char	*line;
	char	**paths;
} t_options;

t_token		**lexer(char *line);

char		**split_join(char **str);

void		split_free(char **str);

char		*strjoinn(char **arr, char *c, int start, int end);

size_t		getnext_whitespace(char *str);

void  		ctrl_c_handler(int sig);

int			is_whitespace(char c);

t_options	*create_options(void);

void		free_options(t_options *o);

char		*get_pwd(void);

void		pwd_one_back(t_options *o);

char		*str_prefix(char *str, char *prefix);

#endif
