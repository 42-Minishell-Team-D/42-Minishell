NAME = minishell

CFLAGS = -g -pthread -Wall -Wextra -Werror #-fsanitize=address
LIBS = -lreadline
RM = rm
LIBFT = ./libs/libft/libft.a
FT_PRINTF_FD = ./libs/ft_printf_fd/libftprintf.a
FILESC = ./src/main.c ./src/init.c \
		./builtins/cd.c ./builtins/echo.c ./builtins/env.c	./builtins/exit.c \
		./builtins/export.c ./builtins/pwd.c ./builtins/unset.c \
		./prompt_handler/parser/parser.c \
		./prompt_handler/create_node.c ./prompt_handler/executor.c \
		./src/functions1.c ./src/utils1.c \

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

.PHONY: all clean fclean re bonus