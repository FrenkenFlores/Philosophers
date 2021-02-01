/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <fflores@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 15:07:04 by fflores           #+#    #+#             */
/*   Updated: 2021/02/01 16:24:03 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h> //threads
#include <stdio.h>  //printf
#include <string.h> // memset
#include <stdlib.h> // malloc, free etc
#include <unistd.h> // write, usleep
#include <sys/time.h> // gettimeofday

typedef struct s_philosopher
{
	int right_fork;
	int left_fork;
	int eating;
	int thinking;
	int sleeping;
	int died;
	int id;
	pthread_t thread_id;
}	t_philosopher;


typedef struct s_data
{
	t_philosopher *philosophers;
	int	number_of_philosophers;
	int number_of_times_each_philosopher_must_eat;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int philosopher_id;
	pthread_mutex_t *mutex_id;
//	pthread_t *thread_id;
}	t_data;

int	 ft_atoi(char *nbr)
{
	int n;

	n = 0;
	if (!nbr)
		return (0);
	while (*nbr >= '0' && *nbr <= '9')
		n = n * 10 + *nbr++ - '0';
	return (n);
}

void start_struct(t_data *data)
{
	data->number_of_philosophers = 0;
	data->philosophers = NULL;
	data->number_of_times_each_philosopher_must_eat = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->philosopher_id = 0;
}

void init_struct(t_data *data, char **argv, int argc)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (data->number_of_philosophers >= 200)
	{
		printf("Do not test with more than 200 philosphers\n");
		exit(EXIT_FAILURE);
	}
	if (data->time_to_die < 60 || data->time_to_eat < 60 || data->time_to_sleep < 60)
	{
		printf("Do not test with time under 60 ms\n");
		exit(EXIT_FAILURE);
	}
}

void init_mutex(t_data *data)
{
	int i;

	i = 0;
	data->mutex_id = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&(data->mutex_id[i]), NULL);
		i++;
	}
}

static void count_time(struct timeval *time)
{
	if (gettimeofday(time, NULL))
		exit(EXIT_FAILURE);	
}

void *count_down(void *data)
{
	struct timeval time;
	t_data *tmp;

	tmp = (t_data *)data;
	usleep(tmp->time_to_die);
	if (!tmp->philosophers[tmp->philosopher_id].eating)
	{
		count_time(&time);
		printf("%d %d died\n", time.tv_usec, tmp->philosopher_id + 1);
		tmp->philosophers[tmp->philosopher_id].died = 1;
	}
}

void *philosopher(void *data)
{
	int id;
	t_data *tmp;
	struct timeval time;
	pthread_t timer;
	
	
	pthread_create(&timer, NULL, count_down, (void *)data);
	pthread_detach(timer);
	tmp = (t_data *)data;
//	id = tmp->philosophers[tmp->philosophers->id];
	if ((id = tmp->philosopher_id) == tmp->number_of_philosophers)
		id = 0;
	tmp->philosophers[id].id = id;
	tmp->philosophers[id].died = 0;
//	printf("%i-%i-%i-%i\n", tmp->number_of_philosophers, tmp->time_to_die, tmp->time_to_eat, tmp->time_to_sleep);
	while(1 && !tmp->philosophers[id].died)
	{
		tmp->philosophers[id].eating = 0;
		tmp->philosophers[id].right_fork = 0;
		tmp->philosophers[id].left_fork = 0;
//		gettimeofday(&time, NULL);
		tmp->philosophers[id].right_fork = pthread_mutex_lock(&tmp->mutex_id[id]);
		count_time(&time);
		printf("%d %d has taken a R fork\n", time.tv_usec, id + 1);
		tmp->philosophers[id].left_fork = pthread_mutex_lock(&tmp->mutex_id[id + 1]);
		count_time(&time);
		printf("%d %d has taken a L fork\n", time.tv_usec, id + 1);
		count_time(&time);
		if (!tmp->philosophers[id].left_fork && !tmp->philosophers[id].right_fork)
		{
			tmp->philosophers[id].eating = 1;
			printf("%d %d is eating\n", time.tv_usec, id + 1);
			usleep (tmp->time_to_eat);
			count_time(&time);
			printf("%d %d is sleeping\n", time.tv_usec, id + 1);
			usleep(tmp->time_to_sleep);
			count_time(&time);
			printf("%d %d is thinking\n", time.tv_usec, id + 1);
			pthread_mutex_unlock(&tmp->mutex_id[id]);
			pthread_mutex_unlock(&tmp->mutex_id[id + 1]);
		}	
	}
	
//	for(int i = 0; i < 100; i++)
//		printf("%i\n", i);
}


void create_threads(t_data *data)
{
	int i;
//	pthread_attr_t attr;

	i = 0;
	data->philosophers = (t_philosopher *)malloc(sizeof(t_philosopher) * data->number_of_philosophers);
//	data->thread_id = (pthread_t *)malloc(sizeof(pthread_t) * data->number_of_philosophers);
//	pthread_attr_init(&attr);
//	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
//	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	while (i < data->number_of_philosophers)
	{
//		data->philosophers[i].id = i;
		data->philosopher_id = i;
		pthread_create(&(data->philosophers[i].thread_id), NULL, philosopher, (void *) data);
		usleep(500);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_join(data->philosophers[i].thread_id, NULL);
		i++;
	}
}
int	main(int argc, char **argv)
{
	t_data data;

	start_struct(&data);
	if (argc == 5 || argc == 6)
	{
		init_struct(&data, argv, argc);
//		printf("%i-%i-%i-%i\n", data.number_of_philosophers, data.time_to_die, data.time_to_eat, data.time_to_sleep);
		init_mutex(&data);
		create_threads(&data);
//		printf("/%d/%d/%d/%d/\n", data.number_of_philosophers, data.time_to_sleep, data.time_to_eat, data.time_to_die);
//		usleep(1000000);		
	}
	else
		printf("Invalid arguments\n");
	return (0);
}