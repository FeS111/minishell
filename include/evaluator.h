#ifndef EVALUATOR_H

typedef struct s_parse_table t_parse_table;
typedef struct s_options t_options;

void	evaluator(t_options *o);
char	*replace_variable(t_options *o, char *str, int start, int end);
char	*replace_home(char *str, int start);
int		get_varlength(char *str);
#endif
