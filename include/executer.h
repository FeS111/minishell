/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:53:10 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/12 12:47:18 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include <unistd.h>

typedef struct s_options		t_options;
typedef struct s_parse_table	t_parse_table;
typedef struct s_parse_cmd		t_parse_cmd;

char	**get_paths(t_options *o);
int		get_in(t_parse_table *table);
int		get_out(t_parse_table *table);
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
