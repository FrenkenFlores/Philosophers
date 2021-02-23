/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores < fflores@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:41:30 by fflores           #+#    #+#             */
/*   Updated: 2021/02/17 14:42:12 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void take_right_fork(t_philosopher *tmp)
{
	tmp->r_fork_id = (tmp->id + 1) % number_of_philosophers;
	tmp->right_fork_flag = pthread_mutex_lock(&mutex_data[tmp->r_fork_id].mutex);
	printf("%ld %d has taken a right fork\n", ft_get_time(), tmp->id + 1);
}

void take_left_fork(t_philosopher *tmp)
{
	tmp->l_fork_id = (tmp->id) % number_of_philosophers;
	tmp->left_fork_flag = pthread_mutex_lock(&mutex_data[tmp->l_fork_id].mutex);
	printf("%ld %d has taken a left fork\n", ft_get_time(), tmp->id + 1);
}

int eat_sleep_think(t_philosopher *tmp, int *first_loop)
{
	tmp->present_time = ft_get_time();
	if (((tmp->present_time - tmp->last_eat_time) > time_to_die) && *first_loop == 0)
		return(0);
	tmp->last_eat_time = ft_get_time();
	printf("%ld %d is eating\n", ft_get_time(), tmp->id + 1);
	ft_count_time(time_to_eat);
	pthread_mutex_unlock(&mutex_data[tmp->l_fork_id].mutex);
	pthread_mutex_unlock(&mutex_data[tmp->r_fork_id].mutex);
	printf("%ld %d is sleeping\n", ft_get_time(), tmp->id + 1);
	ft_count_time(time_to_sleep);
	printf("%ld %d is thinking\n", ft_get_time(), tmp->id + 1);
	*first_loop = 0;
	return (1);
}

void	take_forks(t_philosopher *philo)
{
	philo->left_fork_flag = 1;
	philo->right_fork_flag = 1;
	if (philo->id % 2 == 0)
	{
		take_left_fork(philo);
		take_right_fork(philo);
	}
	else
	{
		take_right_fork(philo);
		take_left_fork(philo);
	}
}