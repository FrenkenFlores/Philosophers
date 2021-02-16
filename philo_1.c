
#include <pthread.h> //threads
#include <stdio.h>  //printf
#include <string.h> // memset
#include <stdlib.h> // malloc, free etc
#include <unistd.h> // write, usleep
#include <sys/time.h> // gettimeofday

typedef struct s_philosopher
{
	long last_eat_time;
	long present_time;
	int right_fork_flag;
	int left_fork_flag;
	int eating;
	int locked;
	int r_fork_id;
	int l_fork_id;
	int thinking;
	int sleeping;
	int died;
	int id;
	pthread_t thread_id;
	pthread_t right_fork_thread;
	pthread_t left_fork_thread;
	pthread_t timer;
	pthread_t put_down_fork;
}	t_philosopher;


typedef struct s_data
{
	t_philosopher *philosophers;
	int number_of_times_each_philosopher_must_eat;
//	int time_to_die;
//	int time_to_eat;
//	int time_to_sleep;
	int philosopher_id;
	pthread_mutex_t *mutex_id;
//	pthread_t *thread_id;
}	t_data;


typedef struct s_mutex
{
	pthread_mutex_t mutex;
	int lock;
}   t_mutex;

t_mutex *mutex_data;
int number_of_philosophers;
long time_to_die;
long time_to_eat;
long time_to_sleep;

int ft_min(int n1, int n2)
{
	return(n1 < n2 ? n1 : n2);
}

int ft_max(int n1, int n2)
{
	return(n1 > n2 ? n1 : n2);
}

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

void start_struct(t_data *data)
{
	number_of_philosophers = 0;
	time_to_die = 0;
	time_to_eat = 0;
	time_to_sleep = 0;
	data->philosophers = NULL;
	data->number_of_times_each_philosopher_must_eat = 0;
	data->philosopher_id = 0;
}

int init_struct(t_data *data, char **argv, int argc)
{
	number_of_philosophers = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]);
	time_to_eat = ft_atoi(argv[3]);
	time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
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

int init_mutex(int number_of_philosophers)
{
	int i;

	i = 0;
	if (!(mutex_data = (t_mutex *)malloc(sizeof(t_mutex) * number_of_philosophers)))
		return (0);
	while (i < number_of_philosophers)
	{
		pthread_mutex_init(&(mutex_data[i].mutex), NULL);
		mutex_data[i].lock = 0;
		i++;
	}
	return (1);
}

long ft_get_time(void)
{
	struct timeval tv;
	long t;

	gettimeofday(&tv, NULL);
	t = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (t);
}



static void ft_count_time(long amount_of_time)
{
	long start;

	start = ft_get_time();
	while (ft_get_time() < start + amount_of_time)
	{
//		printf("%ld\n", ft_get_time());
		usleep(100);
	}
}

int find_free_fork(void)
{
	int i;

	i = 0;
	while (1)
	{
		if (!(mutex_data[i].lock))
			return(i);
		i++;
		if (i == number_of_philosophers)
		{
			i = 0;
			usleep(10000);
		}
	}
	return (0);
}

void *put_down_l_fork(void *philosopher)
{
	struct timeval time;
	t_philosopher *tmp;

	tmp = (t_philosopher *)philosopher;
	tmp->died = 0;
	usleep(60);
	if (!tmp->left_fork_flag && tmp->right_fork_flag)
	{
		pthread_mutex_unlock(&mutex_data[tmp->l_fork_id].mutex);
		mutex_data[tmp->l_fork_id].lock = 0;
		tmp->left_fork_flag = 1;
		gettimeofday(&time, NULL);
		printf("%d %d has put left fork\n", time.tv_usec, tmp->id + 1);
	}
}

void *put_down_r_fork(void *philosopher)
{
	struct timeval time;
	t_philosopher *tmp;

	tmp = (t_philosopher *)philosopher;
	tmp->died = 0;
	usleep(60);
	if (tmp->left_fork_flag && !tmp->right_fork_flag)
	{
		pthread_mutex_unlock(&mutex_data[tmp->r_fork_id].mutex);
		mutex_data[tmp->r_fork_id].lock = 0;
		tmp->right_fork_flag = 1;
		gettimeofday(&time, NULL);
		printf("%d %d has put right fork\n", time.tv_usec, tmp->id + 1);
	}
}

void take_right_fork(t_philosopher *tmp)
{
	tmp->r_fork_id = (tmp->id + 1) % number_of_philosophers;
	tmp->right_fork_flag = pthread_mutex_lock(&mutex_data[tmp->r_fork_id].mutex);
	printf("%ld %d has taken a right fork\n", ft_get_time(), tmp->id + 1);
}

void take_left_fork(t_philosopher *tmp)
{
	tmp->l_fork_id = (tmp->id) % number_of_philosophers;
	tmp->left_fork_flag = pthread_mutex_lock(&mutex_data[tmp->l_fork_id].mutex);
	printf("%ld %d has taken a left fork\n", ft_get_time(), tmp->id + 1);
}

int eat_sleep_think(t_philosopher *tmp, int *first_loop)
{
	tmp->present_time = ft_get_time();
	if (((tmp->present_time - tmp->last_eat_time) > time_to_die) && *first_loop == 0)
		return(0);
	tmp->last_eat_time = ft_get_time();
	printf("%ld %d is eating\n", ft_get_time(), tmp->id + 1);
	ft_count_time(time_to_eat);
	pthread_mutex_unlock(&mutex_data[tmp->l_fork_id].mutex);
	pthread_mutex_unlock(&mutex_data[tmp->r_fork_id].mutex);
	mutex_data[tmp->l_fork_id].lock = 0;
	mutex_data[tmp->r_fork_id].lock = 0;
	printf("%ld %d is sleeping\n", ft_get_time(), tmp->id + 1);
	ft_count_time(time_to_sleep);
	printf("%ld %d is thinking\n", ft_get_time(), tmp->id + 1);
	*first_loop = 0;
	return (1);
}

void *f_philosopher(void *philosopher)
{
	int first_loop;
	t_philosopher *tmp;
	struct timeval time;

	first_loop = 1;
	tmp = (t_philosopher *)philosopher;
	while (1)
	{
		tmp->left_fork_flag = 1;
		tmp->right_fork_flag = 1;
		if (tmp->id % 2 == 0)
		{
			take_left_fork(tmp);
			take_right_fork(tmp);
		}
		else
		{
			take_right_fork(tmp);
			take_left_fork(tmp);
		}
		if (!tmp->left_fork_flag && !tmp->right_fork_flag)
			if(!(eat_sleep_think(tmp, &first_loop)))
			{
				printf("%ld %d died\n", ft_get_time(), tmp->id + 1);
				return (NULL);
			}
	}
}

int create_threads(t_data *data)
{
	int i;
	void *ret;

	i = 0;
	if(!(data->philosophers = (t_philosopher *)malloc(sizeof(t_philosopher) * number_of_philosophers)))
		return (0);
	while (i < number_of_philosophers)
	{
		data->philosophers[i].id = i;
		if ((pthread_create(&(data->philosophers[i].thread_id), NULL, f_philosopher, (void *) &data->philosophers[i])))
			return (0);
		i++;
	}
	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_join(data->philosophers[i].thread_id, &ret);
		if (ret == NULL)
			return (1);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data data;

	start_struct(&data);
	if (argc == 5 || argc == 6)
	{
		if(!(init_struct(&data, argv, argc)))
			return (1);
		if(!(init_mutex(number_of_philosophers)))
			return (1);
		if(!(create_threads(&data)))
			return (1);		
	}
	else
		printf("Invalid arguments\n");
	return (0);
}