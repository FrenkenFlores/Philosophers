/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores < fflores@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:03:19 by fflores           #+#    #+#             */
/*   Updated: 2021/02/17 14:40:30 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

long	 ft_atoi(char *nbr)
{
	long n;

	n = 0;
	if (!nbr)
		return (0);
	while (*nbr >= '0' && *nbr <= '9')
		n = n * 10 + *nbr++ - '0';
	if (*nbr < 0 || *nbr > 0)
	{
		printf("Invalid arguments\n");
		return(0);
	}
	return (n);
}

long ft_get_time(void)
{
	struct timeval tv;
	long t;

	gettimeofday(&tv, NULL);
	t = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (t);
}

void ft_count_time(long amount_of_time)
{
	long start;

	start = ft_get_time();
	while (ft_get_time() < start + amount_of_time)
		usleep(100);
}

void start(t_data *data)
{
	dead = 0;
	end = 0;
	number_of_philosophers = 0;
	time_to_die = 0;
	time_to_eat = 0;
	time_to_sleep = 0;
	data->philosophers = NULL;
	number_of_times_each_philosopher_must_eat = -1;
	data->philosopher_id = 0;
}

int init_data(t_data *data, char **argv, int argc)
{
	number_of_philosophers = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]);
	time_to_eat = ft_atoi(argv[3]);
	time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (number_of_philosophers > 200)
	{
		printf("Do not test with more than 200 philosphers\n");
		return(0);
	}
	if (time_to_die < 60 || time_to_eat < 60 || time_to_sleep < 60)
	{
		printf("Do not test with time under 60 ms\n");
		return(0);
	}
	if (number_of_philosophers < 2)
	{
		printf("Invalid arguments\n");
		return(0);
	}
	return (1);
}