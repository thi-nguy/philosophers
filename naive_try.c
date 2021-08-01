#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void    *routine()
{
    printf("Test from thread\n");
    sleep (3);
    printf("Ending thread\n");
}

int main(void)
{
    pthread_t t1;
    pthread_t t2;

    if (pthread_create(&t1, NULL, &routine, NULL) != 0)
        return (1); // pthread_create: return int
    if (pthread_create(&t2, NULL, &routine, NULL) != 0)
        return (1);
    pthread_join(t1, NULL); // Wait for thread finish
    pthread_join(t2, NULL); // Wait for thread finishhj
    return (0);
}
