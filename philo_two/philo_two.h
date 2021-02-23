/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores < fflores@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:12:11 by fflores           #+#    #+#             */
/*   Updated: 2021/02/23 12:59:39 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

#include <fcntl.h> // O_CREATE, etc
#include <pthread.h> //threads
#include <stdio.h>  //printf
#include <string.h> // memset
#include <stdlib.h> // malloc, free etc
#include <unistd.h> // write, usleep
#include <sys/time.h> // gettimeofday
#include <semaphore.h> // semaphore

typedef struct s_data
{
	pthread_t	pthread;
	long		last_eat_time;
	long		present_time;
	int			id;	
}	t_data;

sem_t	*semaphore;
int		number_of_philosophers;
int		number_of_times_each_philosopher_must_eat;
int		number_of_philosopher_that_have_eat;
long	time_to_die;
long	time_to_eat;
long	time_to_sleep;
int		dead;
int		even;
char	sem_name[3];

int	create_threads(void);
void *check(void *data);
void *f_philosopher(void *data);
int	init_sem(void);
int init_data(char **argv, int argc);
void start(void);
void ft_count_time(long amount_of_time);
long ft_get_time(void);
long	ft_atoi(char *nbr);




#endif