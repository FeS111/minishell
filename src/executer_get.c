#include "../include/minishell.h"

int	get_in(t_parse_table **tables)
{
	int	i;

	i = 0;
	while (tables[i])
		i++;
	i -= 1;
	while (i >= 0)
	{
		if (tables[i]->in == READ)
		{
			if (!ft_strncmp(tables[i]->cmd->cmd, "here_doc", 9))
				return (open("here_doc", O_RDONLY));
			else
				return (open(tables[i]->cmd->cmd, O_RDONLY));
		}
		i--;
	}
	return (dup(STDIN_FILENO));
}

int	get_out(t_parse_table **tables)
{
	int	i;

	i = 0;
	while (tables[i])
		i++;
	i -= 1;
	while (i >= 0)
	{
		if (tables[i]->out == WRITE)
		{
			if (tables[i]->cmd->args
				&& !ft_strncmp(tables[i]->cmd->args[0], ">>", 2))
				return (open(tables[i]->cmd->cmd,
						O_APPEND | O_WRONLY, 0644));
			return (open(tables[i]->cmd->cmd,
					O_CREAT | O_TRUNC | O_WRONLY, 0644));
		}
		i--;
	}
	return (STDOUT_FILENO);
}

char	**get_paths(t_options *o)
{
	char	*path;
	char	**res;

	path = ft_getenv(o, "PATH");
	if (!path)
		return (NULL);
	res = ft_split(path, ':');
	free(path);
	return (res);
}

char	*search_binary(t_options *o, char *cmd)
{
	char	*absolute_path;
	int		i;

	if (cmd[0] == '/' && access(cmd, X_OK) >= 0)
		return (ft_strdup(cmd));
	i = 0;
	split_free(o->paths);
	o->paths = get_paths(o);
	while (o->paths && o->paths[i])
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
	return (NULL);
}

char	**build_args(t_parse_cmd *cmd)
{
	char	**args;
	int		i;
	int		l;

	l = 0;
	while (cmd->args && cmd->args[l])
		l++;
	args = ft_calloc(sizeof(char *), l + 2);
	i = 0;
	args[0] = ft_strdup(cmd->cmd);
	l = -1;
	while (cmd->args && cmd->args[++l])
		args[++i] = ft_strdup(cmd->args[l]);
	return (args);
}
