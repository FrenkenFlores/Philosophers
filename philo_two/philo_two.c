/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores < fflores@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:12:06 by fflores           #+#    #+#             */
/*   Updated: 2021/02/23 12:46:55 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

char *name = "ID";

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
	sem_unlink(name);
	semaphore = sem_open(name, O_CREAT, 0666, number_of_philosophers);
	if (semaphore == SEM_FAILED)
	{
		printf("Error\n");
		return (0);
	}
	return (1);
}


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

void *check(void *data)
{
	while (1)
	{
		if (dead || \
		(number_of_philosopher_that_have_eat == number_of_philosophers))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

int	create_threads(void)
{
	void		*ret;
	pthread_t	count;
	t_data		*data;
	int			i;

	i = 0;
	if (!(data = (t_data *)malloc(sizeof(t_data) * number_of_philosophers)))
	{
		sem_unlink(name);
		sem_close(semaphore);
		return (0);
	}
	if ((pthread_create(&count, NULL, check, NULL)))
	{
		return (0);
	}
	while (i < number_of_philosophers)
	{
		data[i].id = i;
		if (pthread_create(&(data[i].pthread), NULL, f_philosopher, (void *) &data[i]))
		{
			free (data);
			sem_unlink(name);
			sem_close(semaphore);
			return (0);
		}
		if (pthread_detach(data[i].pthread))
		{
			free (data);
			sem_unlink(name);
			sem_close(semaphore);
			return (0);
		}
		i++;
	}
	if (pthread_join(count, &ret))
	{
		free (data);
		sem_unlink(name);
		sem_close(semaphore);
		return (0);
	}
	if (ret == NULL)
	{
		free (data);
		sem_unlink(name);
		sem_close(semaphore);
		return (1);
	}
	free (data);
	sem_unlink(name);
	sem_close(semaphore);
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
