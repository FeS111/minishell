
#include "../include/minishell.h"

void	ft_pwd(t_options *o)
{
	ft_putendl_fd(o->pwd, 1);
}

void	ft_env(t_options *o)
{
	int				i;

	i = -1;
	while (o->env[++i] != NULL)
	{
		ft_putendl_fd(o->env[i], 1);
	}
};

void	ft_unset(t_options *o, char *name)
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
		if (!ft_strnstr(o->env[i], name, ft_strlen(name)))
		{
			env[j] = o->env[i];
			j++;
		}
	}
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
			continue;
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
				break;
			}
		}
	}
	split_free(tmp);
}
