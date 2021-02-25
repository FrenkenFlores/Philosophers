#include "philo_three.h"

static	void	even_group(t_data *tmp)
{
	sem_wait(g_semaphore);
	sem_wait(g_sem_printf);
	printf("%ld %d has taken a right fork\n", ft_get_time(), tmp->id + 1);
	sem_post(g_sem_printf);
	sem_wait(g_semaphore);
	sem_wait(g_sem_printf);
	printf("%ld %d has taken a left fork\n", ft_get_time(), tmp->id + 1);
	sem_post(g_sem_printf);
	tmp->present_time = ft_get_time();
	if ((tmp->present_time - tmp->last_eat_time) > g_time_to_die)
	{
		sem_post(g_semaphore);
		sem_post(g_semaphore);
		g_dead = 1;
		sem_wait(g_sem_printf);
		printf("%ld %d died\n", ft_get_time(), tmp->id + 1);
		exit(0);
	}
	tmp->last_eat_time = ft_get_time();
	sem_wait(g_sem_printf);
	printf("%ld %d is eating\n", ft_get_time(), tmp->id + 1);
	sem_post(g_sem_printf);
	ft_count_time(g_time_to_eat);
	sem_post(g_semaphore);
	sem_post(g_semaphore);
	tmp->present_time = ft_get_time();
	if ((tmp->present_time - tmp->last_eat_time) > g_time_to_die)
	{
		sem_post(g_semaphore);
		sem_post(g_semaphore);
		g_dead = 1;
		sem_wait(g_sem_printf);
		printf("%ld %d died\n", ft_get_time(), tmp->id + 1);
		exit(0);
	}
	sem_wait(g_sem_printf);
	printf("%ld %d is sleeping\n", ft_get_time(), tmp->id + 1);
	sem_post(g_sem_printf);
	ft_count_time(g_time_to_sleep);
	sem_wait(g_sem_printf);
	printf("%ld %d is thinking\n", ft_get_time(), tmp->id + 1);
	sem_post(g_sem_printf);
}

static	void	odd_group(t_data *tmp)
{
	sem_wait(g_sem_printf);
	printf("%ld %d is sleeping\n", ft_get_time(), tmp->id + 1);
	sem_post(g_sem_printf);
	ft_count_time(g_time_to_sleep);
	sem_wait(g_sem_printf);
	printf("%ld %d is thinking\n", ft_get_time(), tmp->id + 1);
	sem_post(g_sem_printf);
	sem_wait(g_semaphore);
	sem_wait(g_sem_printf);
	printf("%ld %d has taken a right fork\n", ft_get_time(), tmp->id + 1);
	sem_post(g_sem_printf);
	sem_wait(g_semaphore);
	sem_wait(g_sem_printf);
	printf("%ld %d has taken a left fork\n", ft_get_time(), tmp->id + 1);
	sem_post(g_sem_printf);
	tmp->present_time = ft_get_time();
	if ((tmp->present_time - tmp->last_eat_time) > g_time_to_die)
	{
		sem_post(g_semaphore);
		sem_post(g_semaphore);
		g_dead = 1;
		sem_wait(g_sem_printf);
		printf("%ld %d died\n", ft_get_time(), tmp->id + 1);
		exit(0);
	}
	tmp->last_eat_time = ft_get_time();
	sem_wait(g_sem_printf);
	printf("%ld %d is eating\n", ft_get_time(), tmp->id + 1);
	sem_post(g_sem_printf);
	ft_count_time(g_time_to_eat);
	sem_post(g_semaphore);
	sem_post(g_semaphore);
	tmp->present_time = ft_get_time();
	if ((tmp->present_time - tmp->last_eat_time) > g_time_to_die)
	{
		sem_post(g_semaphore);
		sem_post(g_semaphore);
		g_dead = 1;
		sem_wait(g_sem_printf);
		printf("%ld %d died\n", ft_get_time(), tmp->id + 1);
		exit(0);
	}
}

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
