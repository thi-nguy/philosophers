#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct sum_s
{
    long long limit;
    long long answer;

} sum_t;

void *sum_runner(void *arg)
{
    sum_t *arg_struct = (sum_t *)arg;

    long long sum = 0;
    for (long long i = 0; i < arg_struct->limit; i++)
        sum += i;
    arg_struct->answer = sum;
    printf("Sum for limit %lld is %lld\n", arg_struct->limit, sum);
    pthread_exit(0);
}

int     main(int ac, char **av)
{
    int num_arg =  ac - 1;
    sum_t sum_arg[num_arg];
    pthread_t thread_ids[num_arg];

    if (ac < 2)
        return (0);
    for (int i = 0; i < num_arg; i++)
    {
        sum_arg[i].limit = atoll(av[i + 1]);
        pthread_create(&thread_ids[i], NULL, sum_runner, &sum_arg[i]);
    }
    for (int i = 0; i < num_arg; i++)
        pthread_join(thread_ids[i], NULL);
    return (0);
}
