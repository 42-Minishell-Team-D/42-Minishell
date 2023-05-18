NAME = minishell # The allmighty!

CFLAGS = -g -pthread -Wall -Wextra -Werror #-fsanitize=address
LIBS = -lreadline
RM = rm
LIBFT = ./libs/libft/libft.a
FT_PRINTF_FD = ./libs/ft_printf_fd/libftprintf.a
FILESC = ./src/main.c ./src/init.c \
		./src/builtins/cd.c ./src/builtins/echo.c ./src/builtins/env.c	./src/builtins/exit.c \
		./src/builtins/export.c ./src/builtins/pwd.c ./src/builtins/unset.c \
		./src/parser/lexical_analyzer.c  ./src/parser/check_syntax.c\
		./src/parser/create_tree.c ./src/parser/parser.c  ./src/parser/lexical_filter.c \
		./src/parser/token_memory.c ./src/parser/get_more_prompt.c ./src/parser/get_more_prompt2.c \
		./src/free/free.c ./src/free/free_if_err.c  \
		./src/executor/executor.c ./src/executor/redirect.c\
		./src/executor/tgps.c  \
		./src/utils1.c \

OBJS = $(FILESC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(FT_PRINTF_FD) $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(LIBFT) $(FT_PRINTF_FD) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIBFT):
	$(MAKE) -C ./libs/libft

$(FT_PRINTF_FD):
	$(MAKE) -C ./libs/ft_printf_fd

clean:
	$(RM) -f $(OBJS)
	$(MAKE) -C libs/libft clean
	$(MAKE) -C ./libs/ft_printf_fd clean
	
fclean: clean
	$(MAKE) -C libs/libft fclean
	$(MAKE) -C ./libs/ft_printf_fd fclean
	$(RM) $(NAME)

re: fclean all

# Leak checker without leaks from readline :D
l: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=.ignore_readline --track-origins=yes --log-file="valgrind.txt" ./minishell

.PHONY: all clean fclean re bonus l