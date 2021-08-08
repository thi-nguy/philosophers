#include "philosophers.h"

int     assign_first_fork(t_philo *one_philo)
{
    if (one_philo->order % 2 == 0) //if philo is at even order, first fork is on the right. otherwise is on the left
        return (RIGHT);
    return (LEFT);
}

void    get_one_fork(t_philo *one_philo, int which_fork)
{
    if (which_fork == RIGHT)
        pthread_mutex_lock(one_philo->right_fork);
    else
        pthread_mutex_lock(one_philo->left_fork);
    print_message(get_time() - g_time_at_beginning, one_philo, TAKE_A_FORK);
}

void    get_both_forks(t_philo *one_philo)
{
    if (assign_first_fork(one_philo) == RIGHT)
    {
        get_one_fork(one_philo, RIGHT);
        get_one_fork(one_philo, LEFT);

    }
    else if (assign_first_fork(one_philo) == LEFT)
    {
        get_one_fork(one_philo, LEFT);
        get_one_fork(one_philo, RIGHT);
    }
}

void    philo_eat(size_t time_at_beginning_of_eating, t_philo *one_philo)
{
    print_message(time_at_beginning_of_eating - g_time_at_beginning, one_philo, EAT);
    count_time(time_at_beginning_of_eating, g_info.time_to_eat);
    one_philo->time_at_end_of_meal = get_time();
	one_philo->current_meal++;
}

void philo_sleep(size_t g_time_at_beginning_of_sleeping, t_philo *one_philo)
{
    print_message(g_time_at_beginning_of_sleeping - g_time_at_beginning, one_philo, SLEEP);
    count_time(g_time_at_beginning_of_sleeping, g_info.time_to_sleep);
}

void		count_time(size_t time, size_t desired_time)
{
	while (get_time() - time < desired_time)
		usleep(10);
}
