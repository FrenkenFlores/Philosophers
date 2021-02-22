/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores < fflores@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:12:06 by fflores           #+#    #+#             */
/*   Updated: 2021/02/22 14:12:09 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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


void start(void)
{
	dead = 0;
	number_of_philosophers = 0;
	time_to_die = 0;
	time_to_eat = 0;
	time_to_sleep = 0;
	number_of_times_each_philosopher_must_eat = -1;
	number_of_philosopher_that_have_eat = 0;
}

int init_data(char **argv, int argc)
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


int	init_sem(void)
{
	semaphore = sem_open("NAME", O_CREAT, 0666, number_of_philosophers);
	if (semaphore == SEM_FAILED)
	{
		printf("Error\n");
		return (0);
	}
	return (1);
}


void *f_philosopher(void *data)
{
	t_data *tmp;

	tmp = (t_data *)data;
	while (1)
	{
		sem_wait(semaphore);
		printf("%d taken right fork\n", tmp->id + 1);
		sem_wait(semaphore);
		printf("%d taken left fork\n", tmp->id + 1);
		printf("%d is eating\n", tmp->id + 1);
		sem_post(semaphore);
		printf("%d put right fork\n", tmp->id + 1);
		sem_post(semaphore);
		printf("%d put right fork\n", tmp->id + 1);
		usleep (10);
	}
	return NULL;
}

int	create_threads(void)
{
	t_data *data;
	int i;

	i = 0;
	if (!(data = (t_data *)malloc(sizeof(t_data) * number_of_philosophers)))
	{
		return (0);
	}
	while (i < number_of_philosophers)
	{
		data[i].id = i;
		if (pthread_create(&(data[i].pthread), NULL, f_philosopher, (void *) &data[i]))
			return (0);
		if (pthread_detach(data[i].pthread))
			return (0);
		i++;
	}
	sleep(10);
	return (1);
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
