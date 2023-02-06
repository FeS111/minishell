#include "../include/minishell.h"

void	ft_export(t_options *o, t_parse_cmd *cmd)
{
	char	**tmp;

	tmp = ft_split(cmd->args[0], '=');
	remove_env(o, tmp[0]);
	add_env(o, tmp[0], tmp[1]);
	split_free(tmp);
	o->last_status = 0;
}

static int	find_git(void)
{
	int		i;
	int		fd;
	char	*pwd;
	char	*tmp;

	i = 0;
	pwd = ft_strdup(".git/HEAD");
	fd = open(pwd, O_RDONLY);
	while (fd < 2 && i < 20)
	{
		tmp = ft_strjoin("../", pwd);
		free(pwd);
		pwd = tmp;
		fd = open(pwd, O_RDONLY);
		i++;
	}
	free(pwd);
	return (fd);
}

static char	*get_current_branch(void)
{
	char	**tmp;
	char	*res;
	char	*line;
	int		i;
	int		fd;

	fd = find_git();
	if (fd < 2)
		return (NULL);
	line = get_next_line(fd);
	close(fd);
	if (!line)
		return (NULL);
	tmp = ft_split(line, '/');
	free(line);
	i = 0;
	while (tmp[i])
		i++;
	res = ft_strtrim(tmp[i -1], "\n");
	split_free(tmp);
	return (res);
}

char	*get_current_folder(t_options *o)
{
	char	**tmp;
	char	*res;
	char	*color;
	int		i;
	char	*branch;

	tmp = ft_split(o->pwd, '/');
	i = 0;
	while (tmp[i])
		i++;
	res = show_status(o);
	res = ft_strjoin_gnl(res, tmp[i - 1]);
	split_free(tmp);
	branch = get_current_branch();
	if (branch)
	{
		res = ft_strjoin_gnl(res, " \033[0;35mgit:(");
		res = ft_strjoin_gnl(res, "\033[31m");
		res = replace_join(res, branch);
		res = ft_strjoin_gnl(res, "\033[0;35m)\033[0;0m");
	}
	res = ft_strjoin_gnl(res, " > ");
	return (res);
}
