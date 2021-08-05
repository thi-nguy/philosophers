#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


void    *routine(void *tid)
{

    long *my_id;

    my_id = (long *)tid;
    printf("This is thread: %ld \n", *my_id);
}

int main(int ac, char **av)
{
    pthread_t tid[3];
    int i;

    i = 0;
    while (i < 3)
    {
        pthread_create(&tid[i], NULL, &routine, (void *)&tid[i]);
        i++;
    }
    pthread_exit(NULL); // wait until pthread_creat finishs, execute all codes inside routin.
}
