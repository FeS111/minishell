MAKEFLAGS += --no-builtin-rules
MAKEFLAGS += --no-builtin-variables

VPATH = src/

# Compiler Variables
CC		= cc
CFLAGSS	= -Wall -Wextra -Werror -g
INCFLAG	= -I include -I printf
READLINE = -L/usr/include -lreadline

# File Variables
NAME	= minishell
SRC		= $(addprefix $(VPATH), main.c buildin_pwd.c lexer.c lexer_util.c split_utils.c tokens.c util.c)
OBJ		= $(addprefix _bin/,$(notdir $(SRC:.c=.o)))
LIBFT	= ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) | $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) $(INCFLAG) $(READLINE) -o $(NAME)

$(LIBFT):
	git submodule update --init
	cd libft && make && make clean

re: fclean all

clean:
	rm -rf _bin

fclean: clean
	rm $(NAME)

_bin :
	mkdir _bin

_bin/%.o : %.c $(LIBFT) | _bin
	$(CC) -c $(CFLAGSS) $(INCFLAG)  $< -o $@

.PHONY: clean fclean re all run
