#include "philosophers.h"
void	execute_thread(void)
{
	int i;

	i = 0;
	while (i < g_info.num_philo)
	{
		g_philo[i].time_at_end_of_meal = g_time_at_beginning;
        pthread_create(&g_thread[i], NULL, routine, (void *)(&g_philo[i]));
		i++;
	}
}


void	*routine(void *arg)
{
	t_philo *one_philo;

	one_philo = (t_philo *)arg;
	while (1)
	{
		get_both_forks(one_philo); // ! mutex lock 2 forks, in ra man hinh taken a fork.
		philo_eat(get_time(), one_philo); // ! in ra man hinh eating. count time, tang so meals_must_eat
        if (pthread_mutex_unlock(one_philo->left_fork) == 0)
            print_message(get_time(), one_philo, PUT_DOWN_A_FORK);
        if (pthread_mutex_unlock(one_philo->right_fork) == 0)
            print_message(get_time(), one_philo, PUT_DOWN_A_FORK);
		if (g_info.meals_must_eat != -1 && one_philo->current_meal == g_info.meals_must_eat)
		{
			g_satisfied_philos++;
            one_philo->is_hungry = 0;
			break;
		}
        philo_sleep(get_time(), one_philo);
		print_message(get_time() - g_time_at_beginning, one_philo, THINK);

		// TODO: dieu kien: Neu meals_must_eat > 0, current_meal = meals_must_eat: ko hungry nua va break khoi vong loop : cham dut
		// TODO: Neu dieu kien chua thoa man thi: sleep -> think
        // TODO: sleep: print message, count time
        // print message think
	}
    return (0);
}
