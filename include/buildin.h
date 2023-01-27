#ifndef BUILDIN_H
# define BUILDIN_H

typedef struct s_options t_options;
typedef struct s_parse_table t_parse_table;

void	panic(t_options *o, int code);
void	ft_pwd(t_options *o);
void	ft_env(t_options *o);
void	ft_export(t_options *o, t_parse_table *cmd);
void	ft_unset(t_options *o, t_parse_table *cmd);
void	ft_cd(t_options *o, t_parse_table *cmd);
void	ft_echo(t_options *o, t_parse_table *cmd);


#endif
