/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:53:07 by fschmid           #+#    #+#             */
/*   Updated: 2023/03/20 09:03:36 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "builtin.h"
# include "minishell.h"

# include <stdlib.h>
# include <sys/fcntl.h>
# include <unistd.h>

typedef enum e_table_types
{
	CMD,
	OPT,
	OPT2,
	ARGS,
}	t_table_types;

typedef enum e_fd
{
	STD_INPUT,
	STD_OUTPUT,
	PIPE_FD,
	WRITE,
	READ,
	HEREDOC,
	APPEND,
}	t_fd;

typedef struct s_parse_cmd
{
	char	*cmd;
	char	*opt;
	char	*opt2;
	char	**args;
	char	*infile;
	char	*outfile;
}			t_parse_cmd;

typedef struct s_parse_table
{
	t_parse_cmd	*cmd;
	int			in;
	int			out;
}			t_parse_table;

typedef struct s_options	t_options;
typedef struct s_token		t_token;

int				parser(t_options *o);

t_parse_cmd		*build_cmd(t_options *o, int *fd, int *i);
t_parse_table	*new_table(t_parse_cmd *cmd, int in, int out);

t_parse_cmd		*handle_token(t_options *o, int *fd, int *i);

char			*get_infile(t_options *o, int *i, int *in, char *infile);
char			*get_outfile(t_options *o, int *i, int *out, char *outfile);
void			redir_panic(t_options *o, int *i);

void			panic_token(char *str);
t_parse_cmd		*new_cmd(char *cmd, char *opt, char *opt2, char **args);
void			free_table(t_parse_table **table);
int				is_woo2(int type);

t_parse_cmd		*here_doc(t_options *o, int *in, int *i);
#endif
