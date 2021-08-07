#include "philosophers.h"

void    philo_eat(size_t time_when_eat, t_philo *one_philo)
{
    print_message(get_time(), one_philo, EAT);
    count_time(time_when_eat, g_info.time_to_eat);
    one_philo->time_at_end_of_meal = get_time();
	one_philo->current_meal++;
}


void		count_time(size_t time, size_t desired_time)
{
	while (get_time() - time < desired_time)
		usleep(100);
}

void philo_sleep(size_t time_when_sleep, t_philo *one_philo)
{
    print_message(get_time(), one_philo, SLEEP);
    count_time(time_when_sleep, g_info.time_to_sleep);
}
