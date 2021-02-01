#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
struct s_data
{
    int a;
    int b;
    int c;
};

void *print_nbr_a(void *data)
{
    struct s_data *tmp;
    tmp = (struct s_data *)data;
    printf("$%d", tmp->a);
}

void *print_nbr_b(void *data)
{
    struct s_data *tmp;
    tmp = (struct s_data *)data;
    printf("$%d", tmp->b);
}

void *print_nbr_c(void *data)
{
    struct s_data *tmp;
    tmp = (struct s_data *)data;
    printf("$%d", tmp->c);
}



int main(void)
{
    pthread_t thread;
    pthread_attr_t attr;
    struct s_data data;

    data.a = 10;
    data.b = 20;
    data.c = 30;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    while (1)
    {
        pthread_create(&thread, &attr, print_nbr_a, (void*) &data);
        pthread_create(&thread, &attr, print_nbr_b, (void *) &data);
        pthread_create(&thread, &attr, print_nbr_c, (void*) &data);
    }
    pthread_join(thread, NULL);
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);
    return (0);
}
