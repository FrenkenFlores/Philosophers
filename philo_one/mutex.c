/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:34:37 by fflores           #+#    #+#             */
/*   Updated: 2021/02/23 14:35:39 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		init_mutex(void)
{
	int i;

	i = 0;
	if (!(g_mutex_data = \
	(t_mutex *)malloc(sizeof(t_mutex) * g_number_of_philosophers)))
		return (0);
	while (i < g_number_of_philosophers)
	{
		if (pthread_mutex_init(&(g_mutex_data[i].mutex), NULL))
		{
			free(g_mutex_data);
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
	while (i < g_number_of_philosophers)
	{
		pthread_mutex_destroy(&g_mutex_data[i].mutex);
		i++;
	}
	free(g_mutex_data);
}
