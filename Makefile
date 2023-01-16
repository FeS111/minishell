VPATH = src/

# Compiler Variables
DOWNLOADFOLDER=dwnlds
CC		= cc
CFLAGSS	= -Wall -Wextra -Werror -g
INCFLAG	= -I include -I libft -I -I$(DOWNLOADFOLDER)/readline_out/include -I printf
READLINE = -L$(DOWNLOADFOLDER)/readline_out/lib -lreadline

# File Variables
NAME	= minishell
SRC		= $(addprefix $(VPATH), main.c buildin_pwd.c lexer.c lexer_util.c split_utils.c tokens.c util.c lexer_get.c signal_handler.c)
OBJ		= $(addprefix _bin/,$(notdir $(SRC:.c=.o)))
LIBFT	= ./libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) | $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) $(INCFLAG) $(READLINE) -o $(NAME)

$(LIBFT):
	git submodule update --init
	cd libft && make && make clean

$(DOWNLOADFOLDER):
	mkdir -p $(DOWNLOADFOLDER)
	curl -s https://ftp.gnu.org/gnu/readline/readline-8.1.2.tar.gz --output $(DOWNLOADFOLDER)/readline-8.1.2.tar.gz
	tar xfz $(DOWNLOADFOLDER)/readline-8.1.2.tar.gz -C $(DOWNLOADFOLDER)
	cd $(DOWNLOADFOLDER)/readline-8.1.2; ./configure --prefix=$(PWD)/dwnlds/readline_out; cd ../../
	make -C $(DOWNLOADFOLDER)/readline-8.1.2
	make install -C $(DOWNLOADFOLDER)/readline-8.1.2

re: fclean all

clean:
	rm -rf _bin

fclean: clean
	rm $(NAME)

_bin :
	mkdir _bin

_bin/%.o : %.c $(LIBFT) $(DOWNLOADFOLDER) | _bin
	$(CC) -c $(CFLAGSS) $(INCFLAG) $< -o $@

.PHONY: clean fclean re all run
