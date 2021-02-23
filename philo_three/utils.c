#include "philo_three.h"

long	ft_atoi(char *nbr)
{
	long n;

	n = 0;
	if (!nbr)
		return (0);
	while (*nbr >= '0' && *nbr <= '9')
		n = n * 10 + *nbr++ - '0';
	if (*nbr < 0 || *nbr > 0)
	{
		printf("Invalid arguments\n");
		return (0);
	}
	return (n);
}

void	start(void)
{
	g_dead = 0;
	g_number_of_philosophers = 0;
	g_time_to_die = 0;
	g_time_to_eat = 0;
	g_time_to_sleep = 0;
	g_number_of_times_each_philosopher_must_eat = -1;
	g_number_of_philosopher_that_have_eat = 0;
	g_sem_name[0] = 'I';
	g_sem_name[1] = 'D';
	g_sem_name[2] = '\0';
}

int		init_data(char **argv, int argc)
{
	g_number_of_philosophers = ft_atoi(argv[1]);
	g_time_to_die = ft_atoi(argv[2]);
	g_time_to_eat = ft_atoi(argv[3]);
	g_time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		g_number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (g_number_of_philosophers > 200)
	{
		printf("Do not test with more than 200 philosphers\n");
		return (0);
	}
	if (g_time_to_die < 60 || g_time_to_eat < 60 || g_time_to_sleep < 60)
	{
		printf("Do not test with time under 60 ms\n");
		return (0);
	}
	if (g_number_of_philosophers < 2)
	{
		printf("Invalid arguments\n");
		return (0);
	}
	return (1);
}

int		init_sem(void)
{
	sem_unlink(g_sem_name);
	g_semaphore = sem_open(g_sem_name, O_CREAT, 0666, \
	g_number_of_philosophers);
	if (g_semaphore == SEM_FAILED)
	{
		printf("Error\n");
		return (0);
	}
	return (1);
}
