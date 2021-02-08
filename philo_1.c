
#include <pthread.h> //threads
#include <stdio.h>  //printf
#include <string.h> // memset
#include <stdlib.h> // malloc, free etc
#include <unistd.h> // write, usleep
#include <sys/time.h> // gettimeofday

typedef struct s_philosopher
{
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
int time_to_die;
int time_to_eat;
int time_to_sleep;

int	 ft_atoi(char *nbr)
{
	int n;

	n = 0;
	if (!nbr)
		return (0);
	while (*nbr >= '0' && *nbr <= '9')
		n = n * 10 + *nbr++ - '0';
	if (*nbr < 0 || *nbr > 0)
	{
		printf("Invalid arguments\n");
		exit(EXIT_FAILURE);
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

void init_struct(t_data *data, char **argv, int argc)
{
	number_of_philosophers = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]);
	time_to_eat = ft_atoi(argv[3]);
	time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	if (number_of_philosophers >= 200)
	{
		printf("Do not test with more than 200 philosphers\n");
		exit(EXIT_FAILURE);
	}
	if (time_to_die < 60 || time_to_eat < 60 || time_to_sleep < 60)
	{
		printf("Do not test with time under 60 ms\n");
		exit(EXIT_FAILURE);
	}
}

void init_mutex(int number_of_philosophers)
{
	int i;

	i = 0;
	mutex_data = (t_mutex *)malloc(sizeof(t_mutex) * number_of_philosophers);
	while (i < number_of_philosophers)
	{
		pthread_mutex_init(&(mutex_data[i].mutex), NULL);
		mutex_data[i].lock = 0;
		i++;
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

static void count_time(struct timeval *time)
{
	if (gettimeofday(time, NULL))
		exit(EXIT_FAILURE);	
}

void *count_down(void *philosopher)
{
	struct timeval time;
	t_philosopher *tmp;

	tmp = (t_philosopher *)philosopher;
	tmp->died = 0;
	usleep(time_to_die);
	if (!tmp->eating)
	{
		count_time(&time);
		printf("%d %d died\n", time.tv_usec, tmp->id + 1);
		tmp->died = 1;
		exit (EXIT_SUCCESS);
	}
	return NULL;
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
		if (pthread_mutex_unlock(&mutex_data[tmp->l_fork_id].mutex))
			exit(EXIT_SUCCESS);
		mutex_data[tmp->l_fork_id].lock = 0;
		tmp->left_fork_flag = 1;
		count_time(&time);
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
		if (pthread_mutex_unlock(&mutex_data[tmp->r_fork_id].mutex))
			exit(EXIT_SUCCESS);
		mutex_data[tmp->r_fork_id].lock = 0;
		tmp->right_fork_flag = 1;
		count_time(&time);
		printf("%d %d has put right fork\n", time.tv_usec, tmp->id + 1);
	}
}

void *take_right_fork(void *philosopher)
{
	t_philosopher *tmp;
	struct timeval time;

	tmp = (t_philosopher *)philosopher;
	tmp->r_fork_id = find_free_fork();
//	tmp->right_fork_flag = 1;
	if ((tmp->right_fork_flag = pthread_mutex_lock(&mutex_data[tmp->r_fork_id].mutex)))
		exit(EXIT_FAILURE);
	mutex_data[tmp->r_fork_id].lock = 1;
	count_time(&time);
	printf("%d %d has taken a right fork\n", time.tv_usec, tmp->id + 1);
	if ((pthread_create(&(tmp->put_down_fork), NULL, put_down_r_fork, (void *)tmp)))
		exit(EXIT_FAILURE);
	if ((pthread_detach(tmp->put_down_fork)))
		exit(EXIT_FAILURE);
}

void *take_left_fork(void *philosopher)
{
	t_philosopher *tmp;
	struct timeval time;

	tmp = (t_philosopher *)philosopher;
	tmp->l_fork_id = find_free_fork();
//	tmp->left_fork_flag = 1;
	if ((tmp->left_fork_flag = pthread_mutex_lock(&mutex_data[tmp->l_fork_id].mutex)))
		exit(EXIT_FAILURE);
	mutex_data[tmp->l_fork_id].lock = 1;
	count_time(&time);
	printf("%d %d has taken a left fork\n", time.tv_usec, tmp->id + 1);
	if ((pthread_create(&(tmp->put_down_fork), NULL, put_down_l_fork, (void *)tmp)))
		exit(EXIT_FAILURE);
	if ((pthread_detach(tmp->put_down_fork)))
		exit(EXIT_FAILURE);
}

void eat_sleep_think(t_philosopher *tmp)
{
	struct timeval time;
	
	tmp->eating = 1;
	count_time(&time);
	printf("%d %d is eating\n", time.tv_usec, tmp->id + 1);
	usleep (time_to_eat);
	if ((pthread_mutex_unlock(&mutex_data[tmp->l_fork_id].mutex)) || 
	(pthread_mutex_unlock(&mutex_data[tmp->r_fork_id].mutex)))
		exit(EXIT_SUCCESS);
	mutex_data[tmp->l_fork_id].lock = 0;
	mutex_data[tmp->r_fork_id].lock = 0;
	tmp->eating = 0;
	count_time(&time);
	printf("%d %d is sleeping\n", time.tv_usec, tmp->id + 1);
	usleep(time_to_sleep);
	count_time(&time);
	printf("%d %d is thinking\n", time.tv_usec, tmp->id + 1);
}

void *f_philosopher(void *philosopher)
{
	t_philosopher *tmp;
	struct timeval time;

	tmp = (t_philosopher *)philosopher;
	tmp->eating = 0;
	while (1)
	{
		tmp->left_fork_flag = 1;
		tmp->right_fork_flag = 1;
//		if ((pthread_create(&(tmp->timer), NULL, count_down, (void *)tmp)))
//			exit(EXIT_FAILURE);
//		if ((pthread_detach(tmp->timer)))
//			exit(EXIT_FAILURE);
		if(pthread_create(&(tmp->left_fork_thread), NULL, take_left_fork, (void *)tmp))
			exit(EXIT_FAILURE);
//		if ((pthread_create(&(tmp->put_down_fork), NULL, put_down_fork, (void *)tmp)))
//			exit(EXIT_FAILURE);
//		if ((pthread_detach(tmp->put_down_fork)))
//			exit(EXIT_FAILURE);
		if(pthread_create(&(tmp->right_fork_thread), NULL, take_right_fork, (void *)tmp))
			exit(EXIT_FAILURE);
//		if ((pthread_create(&(tmp->put_down_fork), NULL, put_down_fork, (void *)tmp)))
//			exit(EXIT_FAILURE);
//		if ((pthread_detach(tmp->put_down_fork)))
//			exit(EXIT_FAILURE);
		if(pthread_join(tmp->left_fork_thread, NULL))
			exit(EXIT_FAILURE);
		if(pthread_join(tmp->right_fork_thread, NULL))
			exit(EXIT_FAILURE);
		if (!tmp->left_fork_flag && !tmp->right_fork_flag)
			eat_sleep_think(tmp);
	}
	
}

void create_threads(t_data *data)
{
	int i;

	i = 0;
	data->philosophers = (t_philosopher *)malloc(sizeof(t_philosopher) * number_of_philosophers);
	while (i < number_of_philosophers)
	{
		data->philosophers[i].id = i;
		pthread_create(&(data->philosophers[i].thread_id), NULL, f_philosopher, (void *) &data->philosophers[i]);
//		usleep(500);
		i++;
	}
	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_join(data->philosophers[i].thread_id, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data data;

	start_struct(&data);
	if (argc == 5 || argc == 6)
	{
		init_struct(&data, argv, argc);
		init_mutex(number_of_philosophers);
		create_threads(&data);		
	}
	else
		printf("Invalid arguments\n");
	return (0);
}