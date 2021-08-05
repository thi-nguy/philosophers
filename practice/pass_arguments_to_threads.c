#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
//each thread carry a number.

void    *routine(void *arg) //arg: pass argument qua routine
{
    int index = *(int*)arg;
    printf("Thread [%d] has:\t%d\n", index, primes[index]);
    free(arg);

}

int main(int ac, char **av)
{
    pthread_t th[10];
    for (int i = 0; i < 10; i++)
    {
        // Khong pass truc tiep gia tri i vi khi thread duoc tao ra nhung no chua that su chay,
        //i cung thay doi
        // Cach giai quyet: malloc gia gi
        int *a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &routine, a) != 0)
            perror("Fail to create thread");
        // khong the free(a) vi thread chua ket thuc. Phai free trong routine.
    }
    for (int i = 0; i < 10; i++)
    {
        if (pthread_join(th[i], NULL) != 0) //wait for thread
        //The pthread_join() function for threads is the equivalent of wait() for processes.
            perror("Fail to join thread");
    }
}
