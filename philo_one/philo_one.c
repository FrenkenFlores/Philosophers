/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fflores <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 14:36:12 by fflores           #+#    #+#             */
/*   Updated: 2021/02/23 14:58:41 by fflores          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	init_dead(t_philosopher *tmp)
{
	g_dead = 1;
	printf("%ld %d died\n", ft_get_time(), tmp->id + 1);
}

void		*f_philosopher(void *philosopher)
{
	int				nbr;
	int				first_loop;
	t_philosopher	*tmp;
	struct timeval	time;

	first_loop = 1;
	nbr = g_number_of_times_each_philosopher_must_eat;
	tmp = (t_philosopher *)philosopher;
	while (1 && nbr != 0)
	{
		if (nbr > 0)
			nbr--;
		take_forks(tmp);
		if (!tmp->left_fork_flag && !tmp->right_fork_flag)
			if (!(eat_sleep_think(tmp, &first_loop)))
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
			return (1);
		if (!(create_threads()))
			return (1);
	}
	else
		printf("Invalid arguments\n");
	return (0);
}
