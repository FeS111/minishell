VPATH = src/

# Compiler Variables
DOWNLOADFOLDER=dwnlds
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g
INCFLAG	= -Iinclude -Ilibft -I$(DOWNLOADFOLDER)/readline_out/include
LINK = -L$(DOWNLOADFOLDER)/readline_out/lib -lreadline -Llibft -lft

# File Variables
NAME	= minishell
SRC		= $(addprefix $(VPATH), main.c \
								buildin2.c \
								buildin.c \
								lexer.c \
								lexer_util.c \
								split_utils.c \
								tokens.c util.c \
								lexer_get.c \
								signal_handler.c \
								lexer_get2.c \
								executer.c \
								str_util.c \
								parser.c \
								parser_utils.c \
								parse_handler.c \
								parse_handler_utils.c \
								parse_handler_redir.c \
								evaluator.c \
			)

OBJ		= $(addprefix _bin/,$(notdir $(SRC:.c=.o)))
LIBFT	= ./libft/libft.a

all: $(NAME)

$(NAME): $(SRC) $(LIBFT) $(DOWNLOADFOLDER)
	$(CC) $(CFLAGS) $(SRC) $(INCFLAG) $(LINK) -o $(NAME)

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

lsan: CFLAG += -fsanitize=address -static-libsan
lsan: all

clean:
	rm -rf _bin

fclean: clean
	rm $(NAME)


.PHONY: clean fclean re all run
