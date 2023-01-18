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
	char	**tmp;
	char	*pwd;
	int		i;

	tmp = ft_split(arg, '/');
	i = -1;
	while (tmp[++i] != NULL)
	{
		if (tmp[i][0] == '.' && tmp[i][1] == '\0')
			continue ;
		else if (tmp[i][0] == '.' && tmp[i][1] == '.')
			pwd_one_back(o);
		else
		{
			pwd = ft_strjoin_gnl(o->pwd, ft_strjoin("/", tmp[i]));
			if (access(pwd, F_OK) != -1)
				o->pwd = pwd;
			else
			{
				ft_printf("cd: no such file or directory: %s\n", tmp[i]);
				break ;
			}
		}
	}
	split_free(tmp);
}
