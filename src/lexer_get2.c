#include "../include/minishell.h"

t_token	*get_variable(char *str)
{
	return (new_token(ft_substr(str, 0, getnext_whitespace(str)), VARIABLE));
}
