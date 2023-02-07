#ifndef EXECUTER_H
# define EXECUTER_H

#include "minishell.h"

char	**get_paths(t_options *o);
int		get_in(t_parse_table **tables);
int		get_out(t_parse_table **tables);
char	*search_binary(t_options *o, char *cmd);
char	**build_args(t_parse_cmd *cmd);

void	execute_child(t_options *o, t_parse_cmd *cmd, int *fd, int *pipefd);
int		run_pipe(t_options *o, int *i, int *fd, pid_t *last_child);
void	execute_pipe(t_options *o, int *i, int *fd);

void	executer(t_options *o);
int		try_builtin(t_options *o, t_parse_cmd *cmd);
void	do_op(t_options *o, t_parse_cmd *cmd);
int		fork_builtin(t_options *o, t_parse_cmd *cmd);

#endif
