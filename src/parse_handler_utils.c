#include "../include/minishell.h"

void	panic_token(char *str)
{
	ft_putstr_fd("syntax error near unexpected token ", 2);
	ft_putendl_fd(str, 2);
}

char	**new_cmd(char *cmd, char *opt, char *opt2, char *args)
{
	char	**new;

	new = malloc(sizeof(char *) * 4 + 1);
	new[CMD] = cmd;
	new[OPT] = opt;
	new[OPT2] = opt2;
	new[ARGS] = args;
	new[4] = NULL;
	return (new);
}

int	is_woo2(int type)
{
	return (type == OPTION || type == OPTION2 || type == WORD);
}
