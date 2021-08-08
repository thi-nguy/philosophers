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
		if (g_dead_philo == 1)
			break ;
		get_both_forks(one_philo); // TODO: mutex lock 2 forks, in ra man hinh taken a fork.
		philo_eat(get_time(), one_philo); // TODO: in ra man hinh eating. count time, tang so meals_must_eat
		if (pthread_mutex_unlock(one_philo->left_fork) == 0)
		{
			print_message(get_time() - g_time_at_beginning, one_philo, PUT_DOWN_LEFT_FORK);
		}
		if (pthread_mutex_unlock(one_philo->right_fork) == 0)
		{
			print_message(get_time() - g_time_at_beginning, one_philo, PUT_DOWN_RIGHT_FORK);
		}
		if (g_info.meals_must_eat != -1 && one_philo->current_meal == g_info.meals_must_eat)
		{
			g_satisfied_philos++;
            one_philo->is_hungry = 0;
			break ;
		}
        philo_sleep(get_time(), one_philo);
		print_message(get_time() - g_time_at_beginning, one_philo, THINK);
        if (get_time() - one_philo->time_at_end_of_meal > g_info.time_to_die)
        {
            print_message(get_time() - g_time_at_beginning, one_philo, DEAD);
			g_dead_philo = 1;
            break ;
        }
	}
    return (0);
}
