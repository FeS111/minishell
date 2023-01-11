MAKEFLAGS += --no-builtin-rules
MAKEFLAGS += --no-builtin-variables

VPATH = src

# Compiler Variables
CC		= cc
CFLAGSS	= -Wall -Wextra -Werror -g
INCFLAG	= 
AR		= ar
ARFLAGS = -rcs
# File Variables
NAME	= minishell 
SRC		= $(addprefix )
OBJ		= $(addprefix _bin/,$(notdir $(SRC:.c=.o)))

.PHONY: clean fclean re all run