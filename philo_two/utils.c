#include "philo_two.h"

long	 ft_atoi(char *nbr)
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
		return(0);
	}
	return (n);
}

void start(void)
{
	dead = 0;
	number_of_philosophers = 0;
	time_to_die = 0;
	time_to_eat = 0;
	time_to_sleep = 0;
	number_of_times_each_philosopher_must_eat = -1;
	number_of_philosopher_that_have_eat = 0;
	sem_name[0] = 'I';
	sem_name[1] = 'D';
	sem_name[2] = '\0';
}

int init_data(char **argv, int argc)
{
	number_of_philosophers = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]);
	time_to_eat = ft_atoi(argv[3]);
	time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (number_of_philosophers > 200)
	{
		printf("Do not test with more than 200 philosphers\n");
		return(0);
	}
	if (time_to_die < 60 || time_to_eat < 60 || time_to_sleep < 60)
	{
		printf("Do not test with time under 60 ms\n");
		return(0);
	}
	if (number_of_philosophers < 2)
	{
		printf("Invalid arguments\n");
		return(0);
	}
	return (1);
}

int	init_sem(void)
{
	sem_unlink(sem_name);
	semaphore = sem_open(sem_name, O_CREAT, 0666, number_of_philosophers);
	if (semaphore == SEM_FAILED)
	{
		printf("Error\n");
		return (0);
	}
	return (1);
}