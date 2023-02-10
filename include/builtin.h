/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:52:49 by fschmid           #+#    #+#             */
/*   Updated: 2023/02/07 13:52:51 by fschmid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct s_options		t_options;
typedef struct s_parse_table	t_parse_table;
typedef struct s_parse_cmd		t_parse_cmd;

void	panic(t_options *o, int code);
void	ft_exit(t_options *o, t_parse_cmd *cmd);
void	ft_pwd(t_options *o);
void	ft_env(t_options *o);
void	ft_export(t_options *o, t_parse_cmd *cmd);
void	ft_unset(t_options *o, t_parse_cmd *cmd);
void	ft_cd(t_options *o, t_parse_cmd *cmd);
void	ft_echo(t_options *o, t_parse_cmd *cmd);
char	*show_status(t_options *o);
void	print_export_shit(t_options *o);
#endif
