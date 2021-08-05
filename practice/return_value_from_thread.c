#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

void    *roll_dice()
{
    int value;
    int *result = malloc(sizeof(int));

    value = (rand() % 6) + 1; //get value randomly from 1 to 6
    *result = value;
    printf("Thread Result: %p\n", result);
    return ((void*)result);
}

int main(void)
{
    int    *res;
    srand(time(NULL));
    pthread_t th;
    if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
        return 1;
    if (pthread_join(th, (void **)&res) != 0) //take double pointer va set value lay tu function roll_dice
        return 1;
    printf("Main Result: %p\n", res);
    printf("Result: %d\n", *res);
    free(res);
    res = NULL;
    return (0);
}
