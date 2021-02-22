/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores < fflores@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:00:51 by fflores           #+#    #+#             */
/*   Updated: 2021/02/22 12:53:17 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PHILO_ONE_H_
# define _PHILO_ONE_H_

# include <pthread.h> //threads
# include <stdio.h>  //printf
# include <string.h> // memset
# include <stdlib.h> // malloc, free etc
# include <unistd.h> // write, usleep
# include <sys/time.h> // gettimeofday

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
}	t_philosopher;

typedef struct	s_data
{
	t_philosopher	*philosophers;
	pthread_mutex_t	*mutex_id;
}	t_data;


typedef struct s_mutex
{
	pthread_mutex_t	mutex;
}   t_mutex;

t_mutex	*mutex_data;
int		number_of_philosophers;
int		number_of_times_each_philosopher_must_eat;
int		number_of_philosopher_that_have_eat;
long	time_to_die;
long	time_to_eat;
long	time_to_sleep;
int		dead;

void	*check_if_dead_end(void *data);
void	*f_philosopher(void *philosopher);
void	take_right_fork(t_philosopher *tmp);
void	take_left_fork(t_philosopher *tmp);
int		eat_sleep_think(t_philosopher *tmp, int *first_loop);
void	take_forks(t_philosopher *philo);
int		init_mutex(void);
void	mutix_destroy(void);
int		create_threads(t_data *data);
long	ft_atoi(char *nbr);
long	ft_get_time(void);
void	ft_count_time(long amount_of_time);
void	start(t_data *data);
int		init_data(char **argv, int argc);

#endif