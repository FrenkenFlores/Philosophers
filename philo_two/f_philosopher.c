/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_philosopher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:55:12 by fflores           #+#    #+#             */
/*   Updated: 2021/02/25 18:55:14 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

static	void	even_group(t_data *tmp)
{
	taking_forks(tmp);
	tmp->present_time = ft_get_time();
	if ((tmp->present_time - tmp->last_eat_time) > g_time_to_die)
	{
		g_dead = 1;
		sem_wait(g_sem_printf);
		printf("%ld %d died\n", ft_get_time(), tmp->id + 1);
		return ;
	}
	tmp->last_eat_time = ft_get_time();
	sem_wait(g_sem_printf);
	printf("%ld %d is eating\n", ft_get_time(), tmp->id + 1);
	sem_post(g_sem_printf);
	ft_count_time(g_time_to_eat);
	sem_post(g_semaphore);
	sem_post(g_semaphore);
	tmp->present_time = ft_get_time();
	if ((tmp->present_time - tmp->last_eat_time) > g_time_to_die)
	{
		g_dead = 1;
		sem_wait(g_sem_printf);
		printf("%ld %d died\n", ft_get_time(), tmp->id + 1);
		return ;
	}
	sleeping_thinking(tmp);
}

static	void	odd_group(t_data *tmp)
{
	sleeping_thinking(tmp);
	taking_forks(tmp);
	tmp->present_time = ft_get_time();
	if ((tmp->present_time - tmp->last_eat_time) > g_time_to_die)
	{
		g_dead = 1;
		sem_wait(g_sem_printf);
		printf("%ld %d died\n", ft_get_time(), tmp->id + 1);
		return ;
	}
	tmp->last_eat_time = ft_get_time();
	sem_wait(g_sem_printf);
	printf("%ld %d is eating\n", ft_get_time(), tmp->id + 1);
	sem_post(g_sem_printf);
	ft_count_time(g_time_to_eat);
	sem_post(g_semaphore);
	sem_post(g_semaphore);
	tmp->present_time = ft_get_time();
	if ((tmp->present_time - tmp->last_eat_time) > g_time_to_die)
	{
		g_dead = 1;
		sem_wait(g_sem_printf);
		printf("%ld %d died\n", ft_get_time(), tmp->id + 1);
		return ;
	}
}

void			*f_philosopher(void *data)
{
	int			nbr;
	t_data		*tmp;

	tmp = (t_data *)data;
	nbr = g_number_of_times_each_philosopher_must_eat;
	tmp->last_eat_time = 0;
	while (1 && nbr != 0 && g_dead != 1)
	{
		if (nbr > 0)
			nbr--;
		tmp->present_time = ft_get_time();
		if (tmp->id % 2)
			even_group(tmp);
		else
			odd_group(tmp);
		if (nbr == 0)
		{
			g_number_of_philosopher_that_have_eat++;
			return (NULL);
		}
	}
	return (NULL);
}
