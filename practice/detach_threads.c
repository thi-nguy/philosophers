// ! detach thread from main.c

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void    *routine()
{
    for (int i = 0; i < 100000; i++)
    {
        sleep(1);
        printf("Finish execution\n");
    }
}

int main(void)
{
    pthread_t th[4];
    int i;

    pthread_mutex_init(&mutex, NULL); //Null = everything to default
    for (i = 0; i < 8; i++)  //create in seperate one
    {
        if (pthread_create(th + i, NULL, &routine, NULL) != 0)
            return 1;
        pthread_detach(th[i]); //
    }
    for (i = 0; i < 8; i++) //join in another loop.
    {
        if (pthread_join(th[i], NULL) != 0)
            return 1;
        printf("Thread %d finishes\n", i);
    }
    pthread_mutex_destroy(&mutex);
    printf("Number of mails: %d\n", mails);
}
