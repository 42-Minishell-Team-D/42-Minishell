# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddantas- <ddantas-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/04 09:52:07 by ddantas-          #+#    #+#              #
#    Updated: 2023/03/05 17:13:02 by ddantas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -g -Wall -Wextra -Werror 
RM = rm
LIBFT = ./libs/libft/libft.a
FILESC = ./src/main.c

OBJS = $(FILESC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIBFT):
	$(MAKE) -C ./libs/libft

clean:
	$(RM) -f $(OBJS)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus