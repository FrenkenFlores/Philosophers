/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 18:57:41 by fflores           #+#    #+#             */
/*   Updated: 2021/02/25 18:57:43 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void			*f_philosopher(t_data *data)
{
	int			nbr;

	nbr = g_number_of_times_each_philosopher_must_eat;
	data->last_eat_time = 0;
	while (1 && nbr != 0 && g_dead != 1)
	{
		if (nbr > 0)
			nbr--;
		data->present_time = ft_get_time();
		if (data->id % 2)
			even_group(data);
		else
			odd_group(data);
		if (nbr == 0)
		{
			g_number_of_philosopher_that_have_eat++;
			return (NULL);
		}
	}
	return (NULL);
}

int				main(int argc, char **argv)
{
	start();
	if (argc == 5 || argc == 6)
	{
		if (!(init_data(argv, argc)))
			return (1);
		if (!(init_sem()))
			return (2);
		if (!(create_processes()))
			return (3);
	}
	else
		printf("Invalid arguments\n");
	return (0);
}
