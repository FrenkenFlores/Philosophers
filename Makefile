# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fflores <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/26 14:28:17 by fflores           #+#    #+#              #
#    Updated: 2021/02/26 14:33:29 by fflores          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean re

all:
	make -C ./philo_one
	make -C ./philo_two
	make -C ./philo_three

clean:
	make clean -C ./philo_one
	make clean -C ./philo_two
	make clean -C ./philo_three

norminette:
	norminette ./philo_one/*.c ./philo_one/*.h
	norminette ./philo_two/*.c ./philo_two/*.h
	norminette ./philo_three/*.c ./philo_three/*.h

re: clean all