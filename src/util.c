#include "../include/minishell.h"
#include <stdio.h>

char	*get_pwd(void)
{
	char	*cwd;

	cwd = ft_calloc(sizeof(char), PATH_MAX);
	getcwd(cwd, PATH_MAX);
	return (cwd);
}

size_t	getnext_whitespace(char *str)
{
	size_t	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (is_whitespace(str[i + 1]) || str[i + 1] == '\0')
			return (i + 1);
	}
	return (0);
}

int	is_whitespace(char c)
{
	if (ft_strchr(" \t\r\v\f\n", c))
		return (1);
	return (0);
}

t_options	*create_options(void)
{
	t_options	*o;
	int			i;
	int			size;
	extern char	**environ;

	ft_printf("\e[1;1H\e[2J");
	size = 0;
	while (environ[size] != NULL)
		size++;
	o = malloc(sizeof(t_options));
	if (!o)
		return (NULL);
	i = -1;
	o->env = malloc(sizeof(char *) * (size + 1));
	while (environ[++i] != NULL)
		o->env[i] = ft_strdup(environ[i]);
	o->env[i] = NULL;
	o->pwd = get_pwd();
	o->line = NULL;
	o->tokens = NULL;
	o->paths = get_paths();
	return (o);
}

void	free_options(t_options *o)
{
	free(o->pwd);
	free(o->line);
	if (o->tokens)
		free_tokens(o->tokens);
	split_free(o->env);
	split_free(o->paths);
	free(o);
}
