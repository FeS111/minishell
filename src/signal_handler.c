#include "../include/minishell.h"

int	g_in_executer;

void	ctrl_c_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		if (!g_in_executer)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

