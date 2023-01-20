#ifndef PARSER_H
# define PARSER_H

#include "../include/minishell.h"

typedef enum e_table_types
{
	CMD,
	OPT,
	OPT2,
	ARG,
} e_table_types;

typedef struct s_parse_table
{
	char	**cmd;
	int		in;
	int		out;
}			t_parse_table;

char			**build_cmd(t_token **tokens, int *in, int *out, int *i);
t_parse_table	*new_table(char **cmd, int in, int out);

char	**handle_io(t_token **tokens, int *in, int *out, int *i);
char	**handle_ior(t_token **tokens, int *in, int *out, int *i);
char	**handle_word(t_token **tokens, int *in, int *out, int *i);
#endif
