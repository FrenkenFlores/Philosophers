#include <pthread.h> //threads
#include <stdio.h>  //printf
#include <string.h> // memset
#include <stdlib.h> // malloc, free etc
#include <unistd.h> // write, usleep
#include <sys/time.h> // gettimeofday
#include <semaphore.h> // semaphore




sem_t semaphore;
int		number_of_philosophers;
int		number_of_times_each_philosopher_must_eat;
int		number_of_philosopher_that_have_eat;
long	time_to_die;
long	time_to_eat;
long	time_to_sleep;
int		dead;





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



int	main(int argc, char **argv)
{
	start();
	if (argc == 5 || argc == 6)
	{
		init_data(argv, argc);
		if (sem_init(&semaphore, 0, number_of_philosophers))
			return (1);
	}
	else
		printf("Invalid arguments\n");
	return (0);
}
