#include "philo_two.h"

void *check(void *data)
{
	while (1)
	{
		if (dead || \
		(number_of_philosopher_that_have_eat == number_of_philosophers))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

int	create_threads(void)
{
	void		*ret;
	pthread_t	count;
	t_data		*data;
	int			i;

	i = 0;
	if (!(data = (t_data *)malloc(sizeof(t_data) * number_of_philosophers)))
	{
		sem_unlink(sem_name);
		sem_close(semaphore);
		return (0);
	}
	if ((pthread_create(&count, NULL, check, NULL)))
	{
		return (0);
	}
	while (i < number_of_philosophers)
	{
		data[i].id = i;
		if (pthread_create(&(data[i].pthread), NULL, f_philosopher, (void *) &data[i]))
		{
			free (data);
			sem_unlink(sem_name);
			sem_close(semaphore);
			return (0);
		}
		if (pthread_detach(data[i].pthread))
		{
			free (data);
			sem_unlink(sem_name);
			sem_close(semaphore);
			return (0);
		}
		i++;
	}
	if (pthread_join(count, &ret))
	{
		free (data);
		sem_unlink(sem_name);
		sem_close(semaphore);
		return (0);
	}
	if (ret == NULL)
	{
		free (data);
		sem_unlink(sem_name);
		sem_close(semaphore);
		return (1);
	}
	free (data);
	sem_unlink(sem_name);
	sem_close(semaphore);
	return (1);
}
