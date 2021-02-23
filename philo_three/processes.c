#include "philo_three.h"

void		*check(void *ptr)
{
	ptr = NULL;
	while (1)
	{
		if (g_dead || \
		(g_number_of_philosopher_that_have_eat == g_number_of_philosophers))
			return (NULL);
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
    int         pid;
    t_data      *data;
	void		*ret;
    pthread_t   check_thread;

	i = 0;
    if (!(data = (t_data *)malloc(sizeof(t_data) * g_number_of_philosophers)))
 		return (clean_sem());
    if (pthread_create(&check_thread, NULL, check, NULL))
		return (clean(data));
	while (i < g_number_of_philosophers)
	{
        data[i].id = i;
        pid = fork();
        if (pid == 0)
        {
            f_philosopher(&data[i]);
            exit(3);
        }
		else if (pid < 0)
			return (clean(data));
		i++;
	}
    if (pthread_join(check_thread, &ret))
		return (clean(data));
	if (ret == NULL)
		return (clean_before_close(data));
	return (clean(data));
}
