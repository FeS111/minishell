#include "../include/minishell.h"

t_options	*create_options(void)
{
	t_options	*o;
	int			i;
	int			size;
	extern char	**environ;

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
	o->paths = get_paths(o);
	o->is_shell = isatty(0);
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
