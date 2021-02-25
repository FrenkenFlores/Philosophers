/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:32:19 by fflores           #+#    #+#             */
/*   Updated: 2021/02/23 14:59:13 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	take_right_fork(t_philosopher *tmp)
{
	tmp->r_fork_id = (tmp->id + 1) % g_number_of_philosophers;
	tmp->right_fork_flag = \
	pthread_mutex_lock(&g_mutex_data[tmp->r_fork_id].mutex);
	pthread_mutex_lock(&g_printf_mutex);
	printf("%ld %d has taken a right fork\n", ft_get_time(), tmp->id + 1);
	pthread_mutex_unlock(&g_printf_mutex);
}

void	take_left_fork(t_philosopher *tmp)
{
	tmp->l_fork_id = (tmp->id) % g_number_of_philosophers;
	tmp->left_fork_flag = \
	pthread_mutex_lock(&g_mutex_data[tmp->l_fork_id].mutex);
	pthread_mutex_lock(&g_printf_mutex);
	printf("%ld %d has taken a left fork\n", ft_get_time(), tmp->id + 1);
	pthread_mutex_unlock(&g_printf_mutex);
}

int		eat_sleep_think(t_philosopher *tmp)
{
	tmp->present_time = ft_get_time();
	if (((tmp->present_time - tmp->last_eat_time) > g_time_to_die))
		return (0);
	tmp->last_eat_time = ft_get_time();
	pthread_mutex_lock(&g_printf_mutex);
	printf("%ld %d is eating\n", ft_get_time(), tmp->id + 1);
	pthread_mutex_unlock(&g_printf_mutex);
	ft_count_time(g_time_to_eat);
	tmp->present_time = ft_get_time();
	if (((tmp->present_time - tmp->last_eat_time) > g_time_to_die))
		return (0);
	pthread_mutex_unlock(&g_mutex_data[tmp->l_fork_id].mutex);
	pthread_mutex_unlock(&g_mutex_data[tmp->r_fork_id].mutex);
	pthread_mutex_lock(&g_printf_mutex);
	printf("%ld %d is sleeping\n", ft_get_time(), tmp->id + 1);
	pthread_mutex_unlock(&g_printf_mutex);
	ft_count_time(g_time_to_sleep);
	pthread_mutex_lock(&g_printf_mutex);
	printf("%ld %d is thinking\n", ft_get_time(), tmp->id + 1);
	pthread_mutex_unlock(&g_printf_mutex);
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
