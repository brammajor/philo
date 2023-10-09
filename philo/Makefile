# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brmajor <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/08 10:28:55 by brmajor           #+#    #+#              #
#    Updated: 2023/10/05 12:53:23 by brmajor          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = src/philo.c src/ft_atoi.c src/argscheck.c src/utils.c src/threading.c src/behavior.c

CC = gcc -g -Wall -Werror -Wextra

NAME = philo

$(NAME): $(SRC) inc/philo.h
	$(CC) $(SRC) -o $(NAME) -lpthread

all: $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
