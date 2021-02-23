/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores < fflores@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:05:40 by fflores           #+#    #+#             */
/*   Updated: 2021/02/23 13:02:56 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int clean(t_data *data)
{
	mutix_destroy();
	free (data->philosophers);
	return (0);
}

void *check_if_dead_end(void *data)
{
	t_data *tmp;

	tmp = (t_data *)data;
	while (1)
	{
		if (dead || \
		(number_of_philosopher_that_have_eat == number_of_philosophers))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

int create_threads(t_data *data)
{
	int i;
	pthread_t check;
	void *ret;

	i = 0;
	if(!(data->philosophers = (t_philosopher *)malloc(sizeof(t_philosopher) * number_of_philosophers)))
		return (0);
	if ((pthread_create(&check, NULL, check_if_dead_end, (void *) &data)))
		return (clean(data));
	while (i < number_of_philosophers)
	{
		data->philosophers[i].id = i;
		if (pthread_create(&(data->philosophers[i].thread_id), \
		NULL, f_philosopher, (void *) &data->philosophers[i]))
			return (clean(data));
		if (pthread_detach(data->philosophers[i].thread_id))
			return (clean(data));
		i++;
	}
	if (pthread_join(check, &ret))
		return (clean(data));
	if (ret == NULL)
	{
		clean(data);
		return (1);
	}
	clean(data);
	return (1);
}