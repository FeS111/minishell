MAKEFLAGS += --no-builtin-rules
MAKEFLAGS += --no-builtin-variables

VPATH = src/

# Compiler Variables
CC		= cc
CFLAGSS	= -Wall -Wextra -Werror -g
INCFLAG	= 
AR		= ar
ARFLAGS = -rcs
# File Variables
NAME	= minishell 
SRC		= $(addprefix $(VPATH), main.c)
OBJ		= $(addprefix _bin/,$(notdir $(SRC:.c=.o)))

_bin :
	mkdir _bin

_bin/%.o : %.c $(LIBFT)/$(LIBFT).a | _bin
	$(CC) -c $(CFLAGSS) $(INCFLAG) $< -o $@

.PHONY: clean fclean re all run