/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:12:00 by fflores           #+#    #+#             */
/*   Updated: 2021/02/25 19:12:22 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <signal.h>
# include <pthread.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>

typedef struct	s_data
{
	long		last_eat_time;
	long		present_time;
	int			id;
	pid_t		pid;
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

int				create_processes(void);
int				init_sem(void);
int				init_data(char **argv, int argc);
long			ft_get_time(void);
long			ft_atoi(char *nbr);
void			*check(void *data);
void			*f_philosopher(t_data *data);
void			start(void);
void			ft_count_time(long amount_of_time);
void			even_group(t_data *tmp);
void			odd_group(t_data *tmp);

#endif
