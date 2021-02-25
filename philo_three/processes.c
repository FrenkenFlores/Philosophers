/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:57:26 by fflores           #+#    #+#             */
/*   Updated: 2021/02/25 19:19:23 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static	int		clean(t_data *data)
{
	free(data);
	sem_unlink("printf");
	sem_close(g_sem_printf);
	sem_unlink(g_sem_name);
	sem_close(g_semaphore);
	return (0);
}

static	int		clean_sem(void)
{
	sem_unlink(g_sem_name);
	sem_close(g_semaphore);
	return (0);
}

static	int		clean_before_close(t_data *data)
{
	clean(data);
	return (1);
}

static	void	sigkill(t_data *data)
{
	int i;

	i = 0;
	if (waitpid(-1, NULL, 0))
	{
		while (i < g_number_of_philosophers)
		{
			kill(data[i].pid, SIGKILL);
			i++;
		}
	}
}

int				create_processes(void)
{
	int			i;
	t_data		*data;

	i = 0;
	if (!(data = (t_data *)malloc(sizeof(t_data) * g_number_of_philosophers)))
		return (clean_sem());
	while (i < g_number_of_philosophers)
	{
		data[i].id = i;
		data[i].pid = fork();
		if (data[i].pid == 0)
		{
			f_philosopher(&data[i]);
			exit(4);
		}
		else if (data[i].pid < 0)
			return (clean(data));
		i++;
	}
	sigkill(data);
	return (clean_before_close(data));
}
