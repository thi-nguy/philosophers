#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo *one_philo;

	one_philo = (t_philo *)arg;
	while (1)
	{
		get_both_forks(one_philo); // ! mutex lock 2 forks, in ra man hinh taken a fork.
		philo_eat(get_time(), one_philo); // ! in ra man hinh eating. count time, tang so meals_must_eat
		if (g_info.meals_must_eat >= 0 && one_philo->current_meal == g_info.meals_must_eat)
		{
			one_philo->is_hungry = 0;
			break;
		}
        philo_sleep(get_time(), one_philo);
		print_message(get_time() - g_start, one_philo, THINK);

		// TODO: dieu kien: Neu meals_must_eat > 0, current_meal = meals_must_eat: ko hungry nua va break khoi vong loop : cham dut
		// TODO: Neu dieu kien chua thoa man thi: sleep -> think
        // TODO: sleep: print message, count time
        // print message think
	}
    return (0);
}




void    get_one_fork(t_philo *one_philo, int which_fork)
{
    if (which_fork == 1)
        pthread_mutex_lock(one_philo->right_fork);
    else
        pthread_mutex_lock(one_philo->left_fork);
    print_message(get_time() - g_start, one_philo, TAKE_A_FORK);

}

size_t			get_time(void)
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}


const char	*get_action_name(int action)
{
	if (action == TAKE_A_FORK)
		return ("taking a fork");
	else if (action == SLEEP)
		return ("sleeping");
	else if (action == EAT)
		return ("eating");
	else if (action == THINK)
		return ("thinking");
	else
		return (NULL);
}



void    create_message(size_t time, t_philo *one_philo, int action)
{
    char *action_name;

    action_name = ft_strdup(get_action_name(action));
    printf("%zu\tPhilosopher number %d is %s\n", time, one_philo->order, action_name);
    free(action_name);
    action_name = NULL;

}

void    print_message(size_t time, t_philo *one_philo, int action)
{

    pthread_mutex_lock(one_philo->message);
    create_message(time, one_philo, action);
    if (action != DEATH)
        pthread_mutex_unlock(one_philo->message);
}


int     assign_first_fork(t_philo *one_philo)
{
    if (one_philo->order % 2 == 0)
        return (RIGHT);
    else
        return (LEFT);

}
void    get_both_forks(t_philo *one_philo)
{
    if (assign_first_fork(one_philo) == RIGHT)
    {
        get_one_fork(one_philo, RIGHT);
        get_one_fork(one_philo, LEFT);
    }
    else
    {
        get_one_fork(one_philo, LEFT);
        get_one_fork(one_philo, RIGHT);
    }
}
