#include "philo_two.h"

long ft_get_time(void)
{
	struct timeval tv;
	long t;

	gettimeofday(&tv, NULL);
	t = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (t);
}

void ft_count_time(long amount_of_time)
{
	long start;

	start = ft_get_time();
	while (ft_get_time() < start + amount_of_time)
		usleep(100);
}