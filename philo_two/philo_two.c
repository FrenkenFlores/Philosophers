/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores < fflores@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:12:06 by fflores           #+#    #+#             */
/*   Updated: 2021/02/23 13:06:37 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void *f_philosopher(void *data)
{
	int 	nbr;
	int		first_loop;
	t_data *tmp;

	first_loop = 1;
	tmp = (t_data *)data;
	nbr = number_of_times_each_philosopher_must_eat;
	while (1 && nbr != 0)
	{
		if (nbr > 0)
			nbr--;
		tmp->present_time = ft_get_time();
		if (tmp->id % 2)
		{
			sem_wait(semaphore);
			printf("%ld %d has taken a right fork\n", ft_get_time(), tmp->id + 1);
			sem_wait(semaphore);
			printf("%ld %d has taken a left fork\n", ft_get_time(), tmp->id + 1);
			tmp->present_time = ft_get_time();
			if (!first_loop && (tmp->present_time - tmp->last_eat_time) > time_to_die)
			{
				dead = 1;
				printf("%ld %d died\n", ft_get_time(), tmp->id + 1);
				return (NULL);
			}
			tmp->last_eat_time = ft_get_time();
			printf("%ld %d is eating\n", ft_get_time(), tmp->id + 1);
			ft_count_time(time_to_eat);
			sem_post(semaphore);
			sem_post(semaphore);
			printf("%ld %d is sleeping\n", ft_get_time(), tmp->id + 1);
			ft_count_time(time_to_sleep);
			printf("%ld %d is thinking\n", ft_get_time(), tmp->id + 1);
		}
		else
		{
			printf("%ld %d is sleeping\n", ft_get_time(), tmp->id + 1);
			ft_count_time(time_to_sleep);
			printf("%ld %d is thinking\n", ft_get_time(), tmp->id + 1);
			sem_wait(semaphore);
			printf("%ld %d has taken a right fork\n", ft_get_time(), tmp->id + 1);
			sem_wait(semaphore);
			printf("%ld %d has taken a left fork\n", ft_get_time(), tmp->id + 1);
			tmp->present_time = ft_get_time();
			if (!first_loop && (tmp->present_time - tmp->last_eat_time) > time_to_die)
			{
				dead = 1;
				printf("%ld %d died\n", ft_get_time(), tmp->id + 1);
				return (NULL);
			}
			tmp->last_eat_time = ft_get_time();
			printf("%ld %d is eating\n", ft_get_time(), tmp->id + 1);
			ft_count_time(time_to_eat);
			sem_post(semaphore);
			sem_post(semaphore);
		}
		if (nbr == 0)
		{
			number_of_philosopher_that_have_eat++;
			return (NULL);
		}
		first_loop = 0;
	}
	return (NULL);
}


int	main(int argc, char **argv)
{
	start();
	if (argc == 5 || argc == 6)
	{
		if (!(init_data(argv, argc)))
			return (1);
		if (!(init_sem()))
			return (1);
		if (!(create_threads()))
			return (1);
	}
	else
		printf("Invalid arguments\n");
	return (0);
}
