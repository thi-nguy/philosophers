#include "philosophers.h"

int main(int ac, char **av)
{
    int i;

	if (check_arg(ac, av) == -1)
        return (0);
    parse_info(ac, av);
	init_info_philo();
	init_fork(); //initialize mutex object (an array because we have several forks, each fork is a mutex)
	g_time_at_beginning = get_time();

	printf("time at begining = %zu\n", g_time_at_beginning);
	execute_thread();
	stop_simulation();
	wait_threads();

	//if (is_philo_dead() == 1)
	//{
	//	// ! free memory
	//	printf("Do something.\n");
	//	return (0);
	//}
	return (0);


}

void		wait_threads(void)
{
	int i;

	i = 0;
	while (i < g_info.num_philo)
	{
		pthread_join(g_thread[i], NULL);
		i++;
	}
}

int stop_simulation(void)
{
	int i;

	while (1)
	{
		i = 0;
		while (i < g_info.num_philo)
		{
			if (g_philo[i].is_hungry && get_time() - g_philo[i].time_at_end_of_meal > g_info.time_to_die)
			{
				print_message(get_time() - g_time_at_beginning, &g_philo[i], DEAD);
				return (1);
			}
			if (g_satisfied_philos && g_satisfied_philos == g_info.num_philo)
				return (1);
			i++;
		}
		//if (g_error == FATAL_ERR)
		//{
		//	ft_putstr_fd("error: fatal\n", 2);
		//	return (1);
		//}
		return (0);
	}
	return (0);

}

void	init_fork(void)
{
	int i;

	i = 0;
	while (i < g_info.num_philo)
	{
		if (pthread_mutex_init(&g_fork[i], NULL) == 0)
			i++;
		else
			break;
	}
}

void	init_info_philo(void)
{
	int i;
	int right_fork_index;

	i = 0;
	while (i < g_info.num_philo)
	{
		g_philo[i].order = i;
		g_philo[i].current_meal = 0;
		g_philo[i].is_hungry = 1;
		right_fork_index = find_right_fork(i);
		g_philo[i].right_fork = &g_fork[right_fork_index];
		g_philo[i].left_fork = &g_fork[i];
		g_philo[i].message = &g_fork[g_info.num_philo];// ! SEGV
		i++;
	}
	g_satisfied_philos = 0;
}

int		find_right_fork(int i)
{
	int index;

	if (i == 0)
		return (g_info.num_philo - 1);
	else
		return (i - 1);
}


void    parse_info(int ac, char **av)
{
   	g_info.num_philo = ft_atoi(av[1]);
    g_info.time_to_die = ft_atoi(av[2]);
    g_info.time_to_eat = ft_atoi(av[3]);
    g_info.time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        g_info.meals_must_eat = ft_atoi(av[5]);
	else
		g_info.meals_must_eat = -1;
}

