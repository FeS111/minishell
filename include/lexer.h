/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luntiet- <luntiet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:43:11 by fschmid           #+#    #+#             */
/*   Updated: 2023/01/13 11:56:27 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

enum	s_token_type
{
	IO,
	IOR,
	PIPE,
	AMBERSAND,
	OPTION,
	OPTION2,
	WORD
};

typedef struct s_token
{
	char				*cmd;
	enum s_token_type	type;
}	t_token;

t_token		new_token(char **cmd);

int	is_word(char *str, int end);

#endif
