#include "../include/minishell.h"

void	ft_export(t_options *o, t_parse_table *cmd)
{
	int		i;
	int		size;
	char	**env;
	char	**tmp;

	size = 0;
	while (o->env[size] != NULL)
		size++;
	env = malloc(sizeof(char *) * (size + 2));
	i = -1;
	while (o->env[++i] != NULL)
		env[i] = o->env[i];
	size = 0;
	env[i] = ft_strdup(cmd->cmd->args[0]);
	env[i + 1] = NULL;
	free(o->env);
	o->env = env;
}

void	ft_cd(t_options *o, t_parse_table *cmd)
{
	chdir(cmd->cmd->args[0]);
	free(o->pwd);
	o->pwd = get_pwd();
}
