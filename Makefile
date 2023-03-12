NAME = minishell

CFLAGS = -g -pthread -Wall -Wextra -Werror #-fsanitize=address
RM = rm
LIBFT = ./libs/libft/libft.a
FILESC = ./src/main.c ./src/functions1.c

OBJS = $(FILESC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIBFT):
	$(MAKE) -C ./libs/libft

clean:
	$(RM) -f $(OBJS)
	make -C libs/libft
	
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus