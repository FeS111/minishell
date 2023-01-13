/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luntiet- <luntiet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:43:11 by fschmid           #+#    #+#             */
/*   Updated: 2023/01/13 12:24:34 by luntiet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# ifndef LIBFT_H
#  include "../libft/libft.h"
# endif

enum	e_token_type
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
	char				*args;
	enum e_token_type	type;
}	t_token;

t_token		new_token(char *args, enum e_token_type type);

int			is_word(char *str, int end);

#endif
