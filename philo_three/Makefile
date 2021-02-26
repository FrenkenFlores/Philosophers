# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fflores <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/26 14:34:50 by fflores           #+#    #+#              #
#    Updated: 2021/02/26 14:49:16 by fflores          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean re

NAME = philo_three
SRCS = groups.c \
	  processes.c \
	  philo_three.c \
	  time_functions.c \
	  utils.c
HEADER = philo_three.h
FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRCS) $(HEADER)
	gcc $(FLAGS) $(SRCS) -o $(NAME)

clean:
	rm $(NAME)

re: clean all
