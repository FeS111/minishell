#ifndef EXECUTER_H

typedef struct s_options t_options;
typedef struct s_parse_table t_parse_table;

char	*search_binary(t_options *o, char *cmd);

char	**get_paths(void);

void	executer(t_options *o);

#endif
