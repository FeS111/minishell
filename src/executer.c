#include "../include/minishell.h"
#include <stdlib.h>

char		**get_paths(void)
{
	char	*path;
	char	**res;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	res = ft_split(path, ':');
	return (res);
}

char	*search_binary(t_options *o, char *cmd)
{
	char	*absolute_path;
	int		i;

	if (access(cmd, F_OK) >= 0)
		return (ft_strdup(cmd));
	i = 0;
	while (o->paths[i])
	{
		absolute_path = ft_strjoin(o->paths[i], "/");
		absolute_path = ft_strjoin_gnl(absolute_path, cmd);
		if (access(absolute_path, F_OK) >= 0)
			return (absolute_path);
		free(absolute_path);
		i++;
	}
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	panic(o, EXIT_FAILURE);
	return (NULL);
}
