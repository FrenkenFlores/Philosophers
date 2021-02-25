/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   groups.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 19:07:47 by fflores           #+#    #+#             */
/*   Updated: 2021/02/25 19:08:07 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static	void	f_die(t_data *tmp)
{
	sem_post(g_semaphore);
	sem_post(g_semaphore);
	g_dead = 1;
	sem_wait(g_sem_printf);
	printf("%ld %d died\n", ft_get_time(), tmp->id + 1);
	exit(0);
}

static	void	sleeping_thinking(t_data *tmp)
{
	sem_wait(g_sem_printf);
	printf("%ld %d is sleeping\n", ft_get_time(), tmp->id + 1);
	sem_post(g_sem_printf);
	ft_count_time(g_time_to_sleep);
	sem_wait(g_sem_printf);
	printf("%ld %d is thinking\n", ft_get_time(), tmp->id + 1);
	sem_post(g_sem_printf);
}

static	void	taking_forks(t_data *tmp)
{
	sem_wait(g_semaphore);
	sem_wait(g_sem_printf);
	printf("%ld %d has taken a right fork\n", ft_get_time(), tmp->id + 1);
	sem_post(g_sem_printf);
	sem_wait(g_semaphore);
	sem_wait(g_sem_printf);
	printf("%ld %d has taken a left fork\n", ft_get_time(), tmp->id + 1);
	sem_post(g_sem_printf);
}

void			even_group(t_data *tmp)
{
	taking_forks(tmp);
	tmp->present_time = ft_get_time();
	if ((tmp->present_time - tmp->last_eat_time) > g_time_to_die)
		f_die(tmp);
	tmp->last_eat_time = ft_get_time();
	sem_wait(g_sem_printf);
	printf("%ld %d is eating\n", ft_get_time(), tmp->id + 1);
	sem_post(g_sem_printf);
	ft_count_time(g_time_to_eat);
	sem_post(g_semaphore);
	sem_post(g_semaphore);
	tmp->present_time = ft_get_time();
	if ((tmp->present_time - tmp->last_eat_time) > g_time_to_die)
		f_die(tmp);
	sleeping_thinking(tmp);
}

void			odd_group(t_data *tmp)
{
	sleeping_thinking(tmp);
	taking_forks(tmp);
	tmp->present_time = ft_get_time();
	if ((tmp->present_time - tmp->last_eat_time) > g_time_to_die)
		f_die(tmp);
	tmp->last_eat_time = ft_get_time();
	sem_wait(g_sem_printf);
	printf("%ld %d is eating\n", ft_get_time(), tmp->id + 1);
	sem_post(g_sem_printf);
	ft_count_time(g_time_to_eat);
	sem_post(g_semaphore);
	sem_post(g_semaphore);
	tmp->present_time = ft_get_time();
	if ((tmp->present_time - tmp->last_eat_time) > g_time_to_die)
		f_die(tmp);
}
