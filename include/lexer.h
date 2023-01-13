/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschmid <fschmid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:43:11 by fschmid           #+#    #+#             */
/*   Updated: 2023/01/13 17:22:02 by fschmid          ###   ########.fr       */
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
	char				*value;
	enum e_token_type	type;
}	t_token;

t_token		*new_token(char *args, enum e_token_type type);

int			is_word(char *str, int end);

t_token		*get_option(char *str);

t_token		*get_option2(char *str);
#endif
