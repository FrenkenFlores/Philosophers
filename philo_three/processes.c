#include "philo_three.h"

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
	i = 0;
	if (waitpid(-1, NULL, 0))
	{
		while (i < g_number_of_philosophers)
		{
			kill(data[i].pid, SIGKILL);
			i++;
		}
	}
	if (ret == NULL)
		return (clean_before_close(data));
	return (clean(data));
}
