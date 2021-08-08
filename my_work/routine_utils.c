#include "philosophers.h"

size_t			get_time(void)
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000); //return time in miliseconds
}

const char	*get_action_name(int action)
{
	if (action == TAKE_A_FORK)
		return ("taking a fork");
  else if (action == PUT_DOWN_LEFT_FORK)
		return ("putting down left fork");
  else if (action == PUT_DOWN_RIGHT_FORK)
		return ("putting down right fork");
	else if (action == SLEEP)
		return ("sleeping");
	else if (action == EAT)
		return ("eating");
	else if (action == THINK)
		return ("thinking");
    else if (action == DEAD)
		return ("dead");
	else
		return (NULL);
}

void    create_message(size_t time, t_philo *one_philo, int action)
{
    char *action_name;

    action_name = ft_strdup(get_action_name(action));
    printf("%zu\tPhilosopher %d is %s\n", time, one_philo->order, action_name);
    free(action_name);
    action_name = NULL;

}

void    print_message(size_t time, t_philo *one_philo, int action)
{

    pthread_mutex_lock(one_philo->message);
    create_message(time, one_philo, action);
    if (action != DEAD)
        pthread_mutex_unlock(one_philo->message);
}
