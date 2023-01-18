#ifndef BUILDIN_H
# define BUILDIN_H

typedef struct s_options t_options;
void	ft_pwd(t_options *o);
void	ft_env(t_options *o);
void	ft_unset(t_options *o, char *name);
void	ft_cd(t_options *o, char *arg);


#endif
