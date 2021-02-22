/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores < fflores@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:04:16 by fflores           #+#    #+#             */
/*   Updated: 2021/02/22 12:53:04 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int init_mutex(void)
{
	int i;

	i = 0;
	if (!(mutex_data = (t_mutex *)malloc(sizeof(t_mutex) * number_of_philosophers)))
		return (0);
	while (i < number_of_philosophers)
	{
		if(pthread_mutex_init(&(mutex_data[i].mutex), NULL))
		{
			free (mutex_data);
			return (0);
		}
		i++;
	}
	return (2);
}

void	mutix_destroy(void)
{
	int i;

	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_mutex_destroy(&mutex_data[i].mutex);
		i++;
	}
	free (mutex_data);
}
