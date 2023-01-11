MAKEFLAGS += --no-builtin-rules
MAKEFLAGS += --no-builtin-variables

VPATH = src/

# Compiler Variables
CC		= cc
CFLAGSS	= -Wall -Wextra -Werror -g
INCFLAG	= -I include -I printf

# File Variables
NAME	= minishell
SRC		= $(addprefix $(VPATH), main.c buildin_pwd.c)
OBJ		= $(addprefix _bin/,$(notdir $(SRC:.c=.o)))
LIBFT	= ./libft/libft.a

$(NAME): $(OBJ) | $(LIBFT)
	$(CC) -o $(NAME) $(CFLAGSS) $(INCFLAG) $(OBJ) $(LIBFT) 

$(LIBFT):
	git submodule update --init
	cd libft && make && make clean

_bin :
	mkdir _bin

_bin/%.o : %.c $(LIBFT) | _bin
	$(CC) -c $(CFLAGSS) $(INCFLAG) $< -o $@

.PHONY: clean fclean re all run
