
# include "../include/minishell.h"

int	is_word(char *str, int end)
{
	int	i;

	i = -1;
	while (str[++i] != '\0' && i < end)
	{
		if (str[i] == '\\' && str[i + 1] != '\0' && (i + 1) < end
			&& ft_strchr("%=+’”()$/_-.\?*~\"", str[i + 1]))
		{
			++i;
			continue ;
		}
		if (ft_isalnum(str[i]) || ft_strchr("{}[]", str[i]))
			continue ;
		return (0);
	}
	return (1);
}
