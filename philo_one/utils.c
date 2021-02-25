/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:04:53 by fflores           #+#    #+#             */
/*   Updated: 2021/02/23 15:06:25 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

long	ft_atoi(char *nbr)
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
		return (0);
	}
	return (n);
}

long	ft_get_time(void)
{
	struct timeval	tv;
	long			t;

	gettimeofday(&tv, NULL);
	t = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (t - g_start_time);
}

void	ft_count_time(long amount_of_time)
{
	long start;

	start = ft_get_time();
	while (ft_get_time() < start + amount_of_time)
		usleep(100);
}

void	start(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	g_start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	g_dead = 0;
	g_number_of_philosophers = 0;
	g_time_to_die = 0;
	g_time_to_eat = 0;
	g_time_to_sleep = 0;
	g_number_of_times_each_philosopher_must_eat = -1;
	g_number_of_philosopher_that_have_eat = 0;
}

int		init_data(char **argv, int argc)
{
	g_number_of_philosophers = ft_atoi(argv[1]);
	g_time_to_die = ft_atoi(argv[2]);
	g_time_to_eat = ft_atoi(argv[3]);
	g_time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		g_number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (g_number_of_philosophers > 200)
	{
		printf("Do not test with more than 200 philosphers\n");
		return (0);
	}
	if (g_time_to_die < 60 || g_time_to_eat < 60 || g_time_to_sleep < 60)
	{
		printf("Do not test with time under 60 ms\n");
		return (0);
	}
	if (g_number_of_philosophers < 2)
	{
		printf("Invalid arguments\n");
		return (0);
	}
	return (1);
}
