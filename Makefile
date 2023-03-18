NAME = minishell

CFLAGS = -g -pthread -Wall -Wextra -Werror -lreadline #-fsanitize=address
RM = rm
LIBFT = ./libs/libft/libft.a
FILESC = ./src/main.c ./src/init.c \
		./builtins/cd.c ./builtins/echo.c ./builtins/env.c	./builtins/exit.c \
		./builtins/export.c ./builtins/pwd.c ./builtins/unset.c \
		./prompt_handler/handler.c \
		./src/functions1.c ./src/utils1.c \


OBJS = $(FILESC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(LIBFT) $(CFLAGS) 

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIBFT):
	$(MAKE) -C ./libs/libft

clean:
	$(RM) -f $(OBJS)
	$(MAKE) -C libs/libft clean
	
fclean: clean
	$(MAKE) -C libs/libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus