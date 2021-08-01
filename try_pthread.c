#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
//each thread carray a number.

void    *routine(void *arg)
{
    sleep(1);
    int index = *(int*)arg;
    printf("%d ", primes[index]);

}

int main(int ac, char **av)
{
    pthread_t th[10];
    for (int i = 0; i < 10; i++)
    {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
            perror("Fail to create thread");
    }
    for (int i = 0; i < 10; i++)
    {
        if (pthread_join(th[i], NULL) != 0) //wait for thread
            perror("Fail to create thread");
    }
}
