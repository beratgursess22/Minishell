NAME = MINISHELL

SRC = executor/execute.c lexer/lexer.c main/main.c parser/parse.c pipe/pipe.c signal/signal.c utils/utils.c built_in/*.c enviroment/*.c expander/*.c herodoc/*.c

CC = cc 

LIBFT = utils/libft/libft.a

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(LIBFT)

$(NAME):
	$(CC) $(SRC) $(LIBFT) -lreadline -o minishell

$(LIBFT):
		make bonus -C utils/libft

clean:
	make clean -C utils/libft

fclean: clean
	rm -rf minishell

re: fclean $(NAME)