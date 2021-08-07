#include "philosophers.h"

int main(int ac, char **av)
{
    if (check_arg(ac, av) == -1)
        return (0);
    parse_info(ac, av);
	init_info_philo();
	init_fork(); //initialize mutex object (an array because we have several forks, each fork is a mutex)
	g_start = get_time();
	execute_thread();
	//if (is_philo_dead() == 1)
	//{
	//	// ! free memory
	//	printf("Do something.\n");
	//	return (0);
	//}
	return (0);


}

void	init_fork(void)
{
	int i;

	i = 0;
	while (i < g_info.num_philo)
	{
		pthread_mutex_init(&g_fork[i], NULL);
		i++;
	}
}

void	init_info_philo(void)
{
	int i;
	int right_fork_index;

	i = 0;
	while (i < g_info.num_philo)
	{
		g_philo[i].order = i; // ! SEGV
		g_philo[i].current_meal = 0;
		g_philo[i].is_hungry = 1;
		right_fork_index = find_right_fork(i);
		g_philo[i].right_fork = &g_fork[right_fork_index];
		g_philo[i].left_fork = &g_fork[i];
		g_philo[i].message = g_message;
		i++;
	}
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

