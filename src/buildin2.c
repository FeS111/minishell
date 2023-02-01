#include "../include/minishell.h"

void	panic(t_options *o, int code)
{
	ft_putendl_fd("exit", 1);
	free_options(o);
	system("leaks minishell");
	exit(code);
}

void	ft_pwd(t_options *o)
{
	ft_putendl_fd(o->pwd, 1);
}

void	ft_env(t_options *o)
{
	int				i;

	i = -1;
	while (o->env[++i] != NULL)
		ft_putendl_fd(o->env[i], 1);
}

void	ft_unset(t_options *o, t_parse_table *cmd)
{
	int		i;
	int		j;
	int		size;
	char	**env;

	size = 0;
	while (o->env[size] != NULL)
		size++;
	env = malloc(sizeof(char *) * (size + 1));
	i = -1;
	j = 0;
	while (o->env[++i] != NULL)
	{
		if (!ft_strnstr(o->env[i], cmd->cmd->args[0], ft_strlen(cmd->cmd->args[0])))
		{
			env[j] = o->env[i];
			j++;
		}
	}
	env[j] = NULL;
	free(o->env);
	o->env = env;
}
void	ft_echo(t_options *o, t_parse_table *cmd)
{
	int		l;
	char	*tmp;

	(void)o;
	l = 0;
	while (cmd->cmd->args[l])
		l++;
	tmp = strjoinn(cmd->cmd->args, " ", 0, l);
	l = -1;
	while (tmp[++l])
	{
		if (tmp[l] == '"' || tmp[l] == '\'')
		{
			tmp = str_replace_char(tmp, tmp[l]);
			break ;
		}
	}
	if (cmd->cmd->opt && ft_strncmp(cmd->cmd->opt, "-n", 2) == 0)
		ft_putstr_fd(tmp, 1);
	else
		ft_putendl_fd(tmp, 1);
	free(tmp);
}

