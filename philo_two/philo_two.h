/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:08:23 by fflores           #+#    #+#             */
/*   Updated: 2021/02/23 14:19:48 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <fcntl.h>
# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>

typedef struct	s_data
{
	pthread_t	pthread;
	long		last_eat_time;
	long		present_time;
	int			id;
}				t_data;

sem_t			*g_sem_printf;
sem_t			*g_semaphore;
int				g_number_of_philosophers;
int				g_number_of_times_each_philosopher_must_eat;
int				g_number_of_philosopher_that_have_eat;
long			g_time_to_die;
long			g_time_to_eat;
long			g_time_to_sleep;
long			g_start_time;
int				g_dead;
int				g_even;
char			g_sem_name[3];

int				create_threads(void);
int				init_sem(void);
int				init_data(char **argv, int argc);
long			ft_get_time(void);
long			ft_atoi(char *nbr);
void			*check(void *data);
void			*f_philosopher(void *data);
void			start(void);
void			ft_count_time(long amount_of_time);

#endif
