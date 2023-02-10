/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:52:59 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/07 13:53:01 by fschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVALUATOR_H

typedef struct s_parse_table	t_parse_table;
typedef struct s_options		t_options;

typedef struct s_eval
{
	int		j;
	int		*replace;
	int		*double_quotes;
	char	*arg;
}	t_eval;

void	evaluator(t_options *o);
char	*replace_variable(t_options *o, char *str, int start, int end);
char	*replace_home(t_options *o, char *str, int start);
int		get_varlength(char *str);
char	*remove_quotes(char *str);
void	evaluator_args(t_options *o, int i);
void	evaluator_cmd(t_options *o, int i);
#endif
