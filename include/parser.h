#ifndef PARSER_H
# define PARSER_H

#include "builtin.h"
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
	PIPE_FD,
	WRITE,
	READ,
} t_fd;

typedef struct s_parse_cmd
{
	char	*cmd;
	char	*opt;
	char	*opt2;
	char	**args;
}			t_parse_cmd;

typedef struct s_parse_table
{
	t_parse_cmd	*cmd;
	int			in;
	int			out;
}			t_parse_table;

typedef struct s_options t_options;
typedef struct s_token t_token;

int				parser(t_options *o);

t_parse_cmd		*build_cmd(t_token **tokens, int *in, int *out, int *i);
t_parse_table	*new_table(t_parse_cmd *cmd, int in, int out);

t_parse_cmd		*handle_io(t_token **tokens, int *in, int *out, int *i);
t_parse_cmd		*handle_word(t_token **tokens, int *in, int *out, int *i);

t_parse_cmd		*left_redir(t_token **tokens, int *in, int *out, int *i);
t_parse_cmd		*right_redir(t_token **tokens, int *in, int *out, int *i);

void			panic_token(char *str);
t_parse_cmd		*new_cmd(char *cmd, char *opt, char *opt2, char **args);
void			free_table(t_parse_table **table);
int				is_woo2(int type);

t_parse_cmd		*here_doc(t_token **tokens, int *in, int *out, int *i);
#endif
