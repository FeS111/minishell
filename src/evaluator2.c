#include "../include/minishell.h"

static char	*handle_arg(t_options *o, char *arg, int j)
{
	int	double_quotes;
	int	replace;

	replace = 1;
	double_quotes = 0;
	if (arg[j] == '"'
		&& !double_quotes && replace)
		double_quotes = 1;
	else if (arg[j] == '\'' && replace && !double_quotes)
		replace = 0;
	else if (arg[j] == '\'' && !replace && !double_quotes)
		replace = 1;
	if (!replace)
		return (arg);
	if (arg[j] == '$')
		arg = replace_variable(o, arg, j, get_varlength(&arg[j]));
	else if (arg[j] == '~')
		arg = replace_home(arg, j);
	return (arg);
}

void	evaluator_args(t_options *o, int i)
{
	int	k;
	int	j;

	k = -1;
	while (o->tables[i]->cmd->args && o->tables[i]->cmd->args[++k])
	{
		j = -1;
		while (o->tables[i]->cmd->args[k]
			&& o->tables[i]->cmd->args[k][++j] != '\0')
			o->tables[i]->cmd->args[k]
				= handle_arg(o, o->tables[i]->cmd->args[k], j);
		o->tables[i]->cmd->args[k]
			= remove_quotes(o->tables[i]->cmd->args[k]);
	}
}

void	evaluator_cmd(t_options *o, int i)
{
	int	j;

	j = -1;
	while (o->tables[i]->cmd->cmd && o->tables[i]->cmd->cmd[++j])
		o->tables[i]->cmd->cmd = handle_arg(o, o->tables[i]->cmd->cmd, j);
	o->tables[i]->cmd->cmd = remove_quotes(o->tables[i]->cmd->cmd);
}

