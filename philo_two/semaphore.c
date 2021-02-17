#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

sem_t sem;
int nbr;

void *f_t1(void *data)
{
	while (1)
	{
		sem_wait(&sem);
		nbr++;
		printf("t1: %d\n", nbr);
		usleep (1000);
		sem_post(&sem);
	}
	return NULL;
}

void *f_t2(void *data)
{
	while (1)
	{
		sem_wait(&sem);
		nbr++;
		printf("t2: %d\n", nbr);
		usleep (1000);
		sem_post(&sem);
	}
	return NULL;
}
void *f_t3(void *data)
{
	while (1)
	{
		sem_wait(&sem);
		if (nbr >= 300)
		{
			printf("done");
			pthread_exit(NULL);
		}
		usleep (100);
		sem_post(&sem);
	}
	return NULL;
}

int	main(void)
{
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;

	nbr = 0;
	sem_init(&sem, 0, 10);
	pthread_create(&t1, NULL, f_t1, NULL);
	pthread_create(&t1, NULL, f_t2, NULL);
	pthread_create(&t1, NULL, f_t3, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	sem_destroy(&sem);
	return (0);
}