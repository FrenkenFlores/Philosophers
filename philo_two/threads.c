/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:58:25 by fflores           #+#    #+#             */
/*   Updated: 2021/02/23 14:04:16 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		*check(void *ptr)
{
	ptr = NULL;
	while (1)
	{
		if (g_dead || \
		(g_number_of_philosopher_that_have_eat == g_number_of_philosophers))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

static	int	clean(t_data *data)
{
	free(data);
	sem_unlink(g_sem_name);
	sem_unlink("printf");
	sem_close(g_sem_printf);
	sem_close(g_semaphore);
	return (0);
}

static	int	clean_sem(void)
{
	sem_unlink(g_sem_name);
	sem_close(g_semaphore);
	return (0);
}

static	int	clean_before_close(t_data *data)
{
	clean(data);
	return (1);
}

int			create_threads(void)
{
	void		*ret;
	pthread_t	count;
	t_data		*data;
	int			i;

	i = 0;
	if (!(data = (t_data *)malloc(sizeof(t_data) * g_number_of_philosophers)))
		return (clean_sem());
	if ((pthread_create(&count, NULL, check, NULL)))
		return (clean(data));
	while (i < g_number_of_philosophers)
	{
		data[i].id = i;
		if (pthread_create(&(data[i].pthread), \
					NULL, f_philosopher, (void *)&data[i]))
			return (clean(data));
		if (pthread_detach(data[i].pthread))
			return (clean(data));
		i++;
	}
	if (pthread_join(count, &ret))
		return (clean(data));
	if (ret == NULL)
		return (clean_before_close(data));
	return (clean(data));
}
