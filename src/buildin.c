#include "../include/minishell.h"

void	ft_export(t_options *o, char *arg)
{
	int		i;
	int		size;
	char	**env;

	size = 0;
	while (o->env[size] != NULL)
		size++;
	env = malloc(sizeof(char *) * (size + 2));
	i = -1;
	while (o->env[++i] != NULL)
	{
		env[i] = o->env[i];
	}
	env[i] = ft_strdup(arg);
	env[i + 1] = NULL;
	free(o->env);
	o->env = env;
}

void	ft_cd(t_options *o, char *arg)
{
	chdir(arg);
	free(o->pwd);
	o->pwd = get_pwd();
}
