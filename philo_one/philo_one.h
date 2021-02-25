/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:07:00 by fflores           #+#    #+#             */
/*   Updated: 2021/02/23 15:07:13 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct	s_philosopher
{
	long		last_eat_time;
	long		present_time;
	int			right_fork_flag;
	int			left_fork_flag;
	int			r_fork_id;
	int			l_fork_id;
	int			id;
	pthread_t	thread_id;
}				t_philosopher;

typedef struct	s_mutex
{
	pthread_mutex_t	mutex;
}				t_mutex;

pthread_mutex_t	g_printf_mutex;
t_mutex			*g_mutex_data;
int				g_number_of_philosophers;
int				g_number_of_times_each_philosopher_must_eat;
int				g_number_of_philosopher_that_have_eat;
long			g_time_to_die;
long			g_time_to_eat;
long			g_time_to_sleep;
long			g_start_time;
int				g_dead;

void			*check_if_dead_end(void *data);
void			*f_philosopher(void *philosopher);
void			take_right_fork(t_philosopher *tmp);
void			take_left_fork(t_philosopher *tmp);
void			take_forks(t_philosopher *philo);
void			mutix_destroy(void);
void			ft_count_time(long amount_of_time);
void			start(void);
int				eat_sleep_think(t_philosopher *tmp, int *first_loop);
int				init_mutex(void);
int				create_threads(void);
int				init_data(char **argv, int argc);
long			ft_atoi(char *nbr);
long			ft_get_time(void);

#endif
