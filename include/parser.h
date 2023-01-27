#ifndef PARSER_H
# define PARSER_H

#include "buildin.h"
#include "minishell.h"

#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

typedef enum e_table_types
{
	CMD,
	OPT,
	OPT2,
	ARGS,
} t_table_types;

typedef enum e_fd
{
	STD_INPUT,
	STD_OUTPUT,
	STD_ERROR,
	PIPE_FD,
	IOR_FD,
	WRITE,
	READ,
} t_fd;

typedef struct s_parse_table
{
	char	**cmd;
	int		in;
	int		out;
}			t_parse_table;

typedef struct s_options t_options;
typedef struct s_token t_token;

void			parser(t_options *o);

char			**build_cmd(t_token **tokens, int *in, int *out, int *i);
t_parse_table	*new_table(char **cmd, int in, int out);

char			**handle_io(t_token **tokens, int *in, int *out, int *i);
char			**handle_word(t_token **tokens, int *in, int *out, int *i);

char			**left_redir(t_token **tokens, int *in, int *out, int *i);
char			**right_redir(t_token **tokens, int *in, int *out, int *i);

void			panic_token(char *str);
char			**new_cmd(char *cmd, char *opt, char *opt2, char *args);
void			free_table(t_parse_table **table);
int				is_woo2(int type);

char			**here_doc(t_token **tokens, int *in, int *out, int *i);
#endif
