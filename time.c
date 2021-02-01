#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>


int main(void)
{
    struct timeval time;
    while (1)
    {
        gettimeofday(&time, NULL);
        printf("%d\n", time.tv_usec);
        usleep(1000000);
    }
    return (0);
}