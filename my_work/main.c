#include "philosophers.h"

int main(int ac, char **av)
{
    int i;

	if (check_arg(ac, av) == -1)
        return (0);
    parse_info(ac, av);
	init_info_philo();
	init_fork(); // TODO: initialize mutex object (an array because we have several forks, each fork is a mutex)
	g_time_at_beginning = get_time();
	execute_thread();
	if (stop_simulation() == 1) // TODO: in case one die or satisfied
	{
		i = 0;
		while (i < g_info.num_philo)
		{
			pthread_detach(g_thread[i]);
			i++;
		}
		free_memory();
		return (0);
	}
	// wait_threads();
	return (0);
}

int stop_simulation(void)
{
	int i;

	while (1)
	{
		i = 0;
		while (i < g_info.num_philo)
		{
			if (g_dead_philo == 1 || g_error == 1)
				return (1);
			if (g_philo[i].is_hungry && get_time() - g_philo[i].time_at_end_of_meal > g_info.time_to_die) // TODO: in case there is only one fork, wait forever to eat.
			{
				print_message(get_time() - g_time_at_beginning, &g_philo[i], DEAD);
				g_dead_philo = 1;
				return (1);
			}
			else if (get_time() - g_philo[i].time_at_end_of_meal > g_info.time_to_die)
			{
				print_message(get_time() - g_time_at_beginning, &g_philo[i], DEAD);
				g_dead_philo = 1;
				return (1); // TODO: in case have meals_must_eat. Stop when satisfied all philos.

			}
			if (g_satisfied_philos == g_info.num_philo) // TODO: in case have meals_must_eat. Stop when satisfied all philos.
				return (1);
			i++;
		}
	}
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


void free_memory(void)
{
	if (g_philo)
	{
		free(g_philo);
		g_philo = NULL;
	}
	if (g_fork)
	{
		free(g_fork);
		g_fork = NULL;
	}
	if (g_thread)
	{
		free(g_thread);
		g_thread = NULL;
	}
}