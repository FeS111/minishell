#include "../include/minishell.h"

void	panic_token(char *str)
{
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putendl_fd(str, 2);
}

t_parse_cmd	*new_cmd(char *cmd, char *opt, char *opt2, char **args)
{
	t_parse_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_parse_cmd));
	new_cmd->cmd = cmd;
	new_cmd->opt = opt;
	new_cmd->opt2 = opt2;
	new_cmd->args = args;
	return (new_cmd);
}

int	is_woo2(int type)
{
	if (type != OPTION && type != OPTION2 && type != WORD)
	{
		return (0);
	}
	return (1);
}
