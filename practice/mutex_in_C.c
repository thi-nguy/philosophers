#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int mails = 0;
int lock = 0;// not safe
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
    pthread_t p1, p2, p3, p4;
    pthread_mutex_init(&mutex, NULL); //Null = everything to default
    if (pthread_create(&p1, NULL, &routine, NULL) != 0)
        return 1;
    if (pthread_create(&p2, NULL, &routine, NULL) != 0)
        return 1;
    if (pthread_create(&p3, NULL, &routine, NULL) != 0)
        return 1;
    if (pthread_create(&p4, NULL, &routine, NULL) != 0)
        return 1;
    if (pthread_join(p1, NULL) != 0)
        return 1;
    if (pthread_join(p2, NULL) != 0)
        return 1;
    if (pthread_join(p3, NULL) != 0)
        return 1;
    if (pthread_join(p4, NULL) != 0)
        return 1;
    pthread_mutex_destroy(&mutex);
    printf("Number of mails: %d\n", mails);
}
