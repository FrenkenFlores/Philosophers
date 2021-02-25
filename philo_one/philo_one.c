/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:36:12 by fflores           #+#    #+#             */
/*   Updated: 2021/02/25 19:20:20 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	init_dead(t_philosopher *tmp)
{
	g_dead = 1;
	pthread_mutex_lock(&g_printf_mutex);
	printf("%ld %d died\n", ft_get_time(), tmp->id + 1);
}

void		*f_philosopher(void *philosopher)
{
	int				nbr;
	t_philosopher	*tmp;

	nbr = g_number_of_times_each_philosopher_must_eat;
	tmp = (t_philosopher *)philosopher;
	tmp->last_eat_time = 0;
	while (1 && nbr != 0 && g_dead != 1)
	{
		if (nbr > 0)
			nbr--;
		take_forks(tmp);
		if (!tmp->left_fork_flag && !tmp->right_fork_flag)
			if (!(eat_sleep_think(tmp)))
				init_dead(tmp);
		if (nbr == 0)
		{
			g_number_of_philosopher_that_have_eat++;
			return (NULL);
		}
	}
	return (NULL);
}

int			main(int argc, char **argv)
{
	start();
	if (argc == 5 || argc == 6)
	{
		if (!(init_data(argv, argc)))
			return (1);
		if (!(init_mutex()))
			return (2);
		if (!(create_threads()))
			return (3);
	}
	else
		printf("Invalid arguments\n");
	return (0);
}
