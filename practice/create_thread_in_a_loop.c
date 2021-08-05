#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void    *routine()
{
    for (int i = 0; i < 100000; i++)
    {
        pthread_mutex_lock(&mutex);
        mails++; //no other thread will access to it if we have mutex
        pthread_mutex_unlock(&mutex);
        //! not safe way:
        //if (lock == 1)
        //{
        //     wait until the lock is 0
        //}
        //lock = 1; //khi do something
        //lock = 0; //when done doing something
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
        printf("Thread %d startes\n", i);
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
