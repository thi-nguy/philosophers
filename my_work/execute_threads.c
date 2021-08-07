#include "philosophers.h"
void	execute_thread(void)
{
	int i;

	i = 0;
	while (i < g_info.num_philo)
	{
		g_philo[i].time_at_end_of_meal = g_start;
        pthread_create(&g_thread[i], NULL, routine, (void *)(&g_philo[i]));
		i++;
	}
}
