/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:59:39 by fflores           #+#    #+#             */
/*   Updated: 2021/02/23 15:00:54 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	clean(t_philosopher *philosophers)
{
	mutix_destroy();
	free(philosophers);
	return (0);
}

static int	clean_before_exit(t_philosopher *philosophers)
{
	clean(philosophers);
	return (1);
}

void		*check_if_dead_end(void *tmp)
{
	tmp = NULL;
	while (1)
	{
		if (g_dead || \
		(g_number_of_philosopher_that_have_eat == g_number_of_philosophers))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

int			create_threads(void)
{
	int				i;
	pthread_t		check;
	t_philosopher	*philosophers;
	void			*ret;

	i = -1;
	if (!(philosophers = \
	(t_philosopher *)malloc(sizeof(t_philosopher) * g_number_of_philosophers)))
		return (0);
	if ((pthread_create(&check, NULL, check_if_dead_end, NULL)))
		return (clean(philosophers));
	while (++i < g_number_of_philosophers)
	{
		philosophers[i].id = i;
		if (pthread_create(&(philosophers[i].thread_id), \
		NULL, f_philosopher, (void *)&philosophers[i]))
			return (clean(philosophers));
		if (pthread_detach(philosophers[i].thread_id))
			return (clean(philosophers));
	}
	if (pthread_join(check, &ret))
		return (clean(philosophers));
	if (ret == NULL)
		return (clean_before_exit(philosophers));
	return (clean(philosophers));
}
