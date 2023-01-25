#ifndef EVALUATOR_H

typedef struct s_parse_table t_parse_table;

void	evaluator(t_parse_table **cmds);
char	*replace_variable(char *str, int start, int end);
#endif
