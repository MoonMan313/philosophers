# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: evelina <evelina@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/12 10:23:25 by cdionna           #+#    #+#              #
#    Updated: 2021/07/28 15:56:04 by evelina          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

HEADER = include/philo.h

SRC = $(addprefix src/, utils.c main.c init.c simulation.c)

O_FILE = $(SRC:.c=.o)

C_FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(O_FILE)
	@gcc $(C_FLAGS) $(O_FILE) -o $(NAME) -lpthread

%.o: %.c $(HEADER)
	@gcc -c $(C_FLAGS) $< -o $@

clean:
	@rm -rf $(O_FILE)

fclean: clean
	@rm -rf $(NAME)

re:		fclean all

.PHONY : all clean fclean re