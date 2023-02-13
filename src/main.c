/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:55:56 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/13 13:42:00 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_in_executer;

void	history(t_options *o)
{
	free_tokens(o->tokens);
	free_table(o->tables);
	o->tokens = NULL;
	o->tables = NULL;
	if (o->line)
	{
		if (ft_strlen(o->line))
			add_history(o->line);
		free(o->line);
		o->line = NULL;
	}
	unlink("here_doc");
}

void	shell(t_options *o)
{
	char	*folder;

	g_in_executer = 0;
	folder = get_current_folder(o);
	o->line = readline(folder);
	free(folder);
	if (!o->line)
		panic(o, 0);
	if (lexer(o) == -1)
		return (history(o));
	if (parser(o) == -1)
		return (history(o));
	evaluator(o);
	executer(o);
	history(o);
}

// void	debug_shell(t_options *o)
// {
// 	char	*folder;
// 	int		j;
//
// 	g_in_executer = 0;
// 	folder = get_current_folder(o);
// 	o->line = readline(folder);
// 	free(folder);
// 	if (lexer(o) == -1)
// 		return (history(o));
// 	j = 0;
// 	ft_putendl_fd("==================================", 1);
// 	ft_putendl_fd("lexer done", 1);
// 	ft_putendl_fd("==================================", 1);
// 	while (o->tokens[j])
// 	{
// 		ft_printf("%s %d\n", o->tokens[j]->value, o->tokens[j]->type);
// 		j++;
// 	}
// 	int par = parser(o);
// 	ft_putendl_fd("==================================", 1);
// 	ft_putendl_fd("parser done", 1);
// 	ft_putendl_fd("==================================", 1);
// 	ft_putnbr_fd(par, 1);
// 	ft_putchar_fd('\n', 1);
// 	if (par == -1)
// 		return (history(o));
// 	if (o->tables)
// 	{
// 		j = 0;
// 		while (o->tables[j])
// 		{
// 			ft_printf("%s, %s, %s, %s, %s, %s, %i, %i\n",
// 			o->tables[j]->cmd->cmd, o->tables[j]->cmd->opt,
// 			o->tables[j]->cmd->opt2,
// 			o->tables[j]->cmd->args ? o->tables[j]->cmd->args[0] : NULL,
// 			o->tables[j]->cmd->infile, o->tables[j]->cmd->outfile,
// 			o->tables[j]->in, o->tables[j]->out);
// 			j++;
// 		}
// 	}
// 	evaluator(o);
// 	ft_putendl_fd("==================================", 1);
// 	ft_putendl_fd("evaluator done", 1);
// 	ft_putendl_fd("==================================", 1);
// 	j = 0;
// 	while (o->tables[j])
// 	{
// 		ft_printf("%s, %s, %s, %s, %s, %s, %i, %i\n", o->tables[j]->cmd->cmd,
// 		o->tables[j]->cmd->opt, o->tables[j]->cmd->opt2,
// 		o->tables[j]->cmd->args ? o->tables[j]->cmd->args[0] : NULL,
// 		o->tables[j]->cmd->infile, o->tables[j]->cmd->outfile,
// 		o->tables[j]->in, o->tables[j]->out);
// 		j++;
// 	}
// 	ft_putendl_fd("==================================", 1);
// 	executer(o);
// 	ft_putendl_fd("==================================", 1);
// 	ft_putendl_fd("executer done", 1);
// 	ft_putendl_fd("==================================", 1);
// 	history(o);
// 	// sleep(5);
// }

int	main(void)
{
	t_options		*o;

	o = create_options();
	if (o->is_shell)
		ft_printf("\e[1;1H\e[2J");
	else
		return (ft_putendl_fd("Use a shell, dude!", 2), panic(o, 1), 0);
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
		shell(o);
	panic(o, 0);
}
