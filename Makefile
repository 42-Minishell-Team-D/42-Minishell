NAME = minishell

CFLAGS = -g -pthread -Wall -Wextra -Werror -lreadline #-fsanitize=address
RM = rm
LIBFT = ./libs/libft/libft.a
FILESC = ./src/main.c ./src/init.c \
		./src/functions1.c ./src/functions2.c

OBJS = $(FILESC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LIBFT) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIBFT):
	$(MAKE) -C ./libs/libft

clean:
	$(RM) -f $(OBJS)
	$(MAKE) -C libs/libft clean
	
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C libs/libft fclean

re: fclean all

.PHONY: all clean fclean re bonus