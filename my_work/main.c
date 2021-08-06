#include "philosophers.h"

int main(int ac, char **av)
{
    if (check_arg(ac, av) == -1)
        return (0);
    parse_info(ac, av);
	init_info_philo();
	init_fork();
	execute_thread();
	if (is_philo_dead() == 1)
	{
		// ! free memory
		printf("Do something.\n");
		return (0);
	}
	return (0);


}

void	*routine(void)
{
	while (1)
	{
		
	}
}

void	execute_thread(void)
{
	int i;

	i = 0;
	while (i < g_info.num_philo)
	{
		pthread_create(&g_thread[i], NULL, routine, NULL);
		i++;
	}
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
		g_philo[i].current_meal = 0;
		g_philo[i].is_hungry = 1;
		right_fork_index = find_right_fork(i);
		g_philo[i].right_fork = &g_fork[right_fork_index];
		g_philo[i].left_fork = &g_fork[i];
		// g_philo[i].mutex = ;
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

int     check_arg(int ac, char **av)
{
    if (ac < 5 || ac > 6)
    {
        printf("Number of arguments is not correct.\n");
        return (-1);
    }
	if (check_isdigit(ac, av) == -1)
		return (-1);
	if (check_int(ac, av) == -1)
		return (-1);
	return (1);
}

int	check_isdigit(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] == '+')
			j++;
		if (av[i][j] == '-')
        {
            printf("Arguments should be positive.\n");
            return (-1);
        }
		while (av[i][j] != '\0')
		{
			if (ft_isdigit(av[i][j]) == 1)
				j++;
			else
			{
				printf("Arguments should be numbers.\n");
				return (-1);
			}
		}
		i++;
	}
	return (1);
}

int	check_int(int ac, char **av)
{
	int			i;
	long int	num;

	i = 1;
	while (i < ac)
	{
		num = ft_atoi(av[i]);
		if (num < -2147483648 || num > 2147483647)
        {
            printf("Argument is out of scope.\n");
			return (-1);
        }
		i++;
	}
	return (1);
}
