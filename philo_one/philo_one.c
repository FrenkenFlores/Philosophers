/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores < fflores@student.21-school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 14:42:36 by fflores           #+#    #+#             */
/*   Updated: 2021/02/17 14:52:40 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void *check_if_dead_end(void *data)
{
	t_data *tmp;

	tmp = (t_data *)data;
	while (1)
	{
		if (dead || end)
		{
			mutix_destroy();
			return (NULL);
		}
		usleep(100);
	}
}

void *f_philosopher(void *philosopher)
{
	int nbr;
	int first_loop;
	t_philosopher *tmp;
	struct timeval time;

	first_loop = 1;
	nbr = number_of_times_each_philosopher_must_eat;
	tmp = (t_philosopher *)philosopher;
	while (1 && nbr != 0)
	{
		if (nbr > 0)
			nbr--;
		take_forks(tmp);
		if (!tmp->left_fork_flag && !tmp->right_fork_flag)
			if(!(eat_sleep_think(tmp, &first_loop)))
			{
				dead = 1;
				printf("%ld %d died\n", ft_get_time(), tmp->id + 1);
			}
		if (nbr == 0)
			end = 1;
	}
}

int	main(int argc, char **argv)
{
	t_data data;

	start(&data);
	if (argc == 5 || argc == 6)
	{
		if(!(init_data(&data, argv, argc)))
			return (1);
		if(!(init_mutex(number_of_philosophers)))
			return (1);
		if(!(create_threads(&data)))
			return (1);		
	}
	else
		printf("Invalid arguments\n");
	free (data.philosophers);
	return (0);
}
