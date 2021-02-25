#include "philo_three.h"

void		*check(void *ptr)
{
	int i;
	t_data *tmp;

	i = 0;
	tmp = (t_data *)ptr;
	while (1)
	{
	i = 0;
	while(i < g_number_of_philosophers)
	{
//		wait(NULL);
		waitpid(tmp[i].pid, NULL, 0);
		i++;
		printf("@2");
	}
		usleep(100);
	}
	return (NULL);
}

static	int	clean(t_data *data)
{
	free(data);
	sem_unlink(g_sem_name);
	sem_close(g_semaphore);
	return (0);
}

static	int	clean_sem(void)
{
	sem_unlink(g_sem_name);
	sem_close(g_semaphore);
	return (0);
}

static	int	clean_before_close(t_data *data)
{
	clean(data);
	return (1);
}

int			create_processes(void)
{
	int			i;
    t_data      *data;
	void		*ret;
    pthread_t   check_thread;

	i = 0;
    if (!(data = (t_data *)malloc(sizeof(t_data) * g_number_of_philosophers)))
 		return (clean_sem());
	while (i < g_number_of_philosophers)
	{
        data[i].id = i;
        data[i].pid = fork();
        if (data[i].pid == 0)
        {
            f_philosopher(&data[i]);
            exit(4);
        }
		else if (data[i].pid < 0)
			return (clean(data));
		i++;
	}
    // if (pthread_create(&check_thread, NULL, check, (void *)&data))
	// 	return (clean(data));
    // if (pthread_join(check_thread, &ret))
	// 	return (clean(data));
	i = 0;
	if (waitpid(data[i].pid, NULL, 0))
	{
		while (i < g_number_of_philosophers)
		{
			kill(data[i].pid, SIGKILL);
			i++;
		}
	}
// 	while(i < g_number_of_philosophers)
// 	{
// 		waitpid(data[i].pid, NULL, 0);
// 		i++;
// //		printf("@2");
// 	}
//	printf("\n<<%d>>\n", g_dead);
	if (ret == NULL)
		return (clean_before_close(data));
	return (clean(data));
}
