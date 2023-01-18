#ifndef EXECUTER_H

typedef struct s_options t_options;

char	*search_binary(t_options *o, char *cmd);

char	**get_paths(void);

#endif
