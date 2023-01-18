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
	WORD,
	VARIABLE
};

typedef struct s_token
{
	char				*value;
	enum e_token_type	type;
}	t_token;

t_token		*new_token(char *args, enum e_token_type type);
void		free_tokens(t_token **tokens);

t_token		*get_quoted(char *str);
t_token		*get_variable(char *str);
t_token		*get_option(char *str);
t_token		*get_io(char *str);
t_token		*get_pipe(char *str);
t_token		*get_ampersand(char *str);

int			is_word(char *str, int end);
int			count_whitespace(char *line);

#endif
