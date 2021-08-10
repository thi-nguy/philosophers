/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-nguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 09:52:19 by thi-nguy          #+#    #+#             */
/*   Updated: 2021/08/10 09:55:12 by thi-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_fork(void)
{
	int	i;

	i = 0;
	while (i < g_info.num_philo)
	{
		if (pthread_mutex_init(&g_fork[i], NULL) == -1)
		{
			g_error = 1;
			break ;
		}
		else
			i++;
	}
}

void	init_info_philo(void)
{
	int	i;
	int	left_fork_index;

	if (init_global_var() == 0)
	{
		g_error = 1;
		return ;
	}
	i = 0;
	while (i < g_info.num_philo)
	{
		g_philo[i].order = i;
		g_philo[i].current_meal = 0;
		g_philo[i].is_hungry = 1;
		left_fork_index = find_left_fork(i);
		g_philo[i].left_fork = &g_fork[left_fork_index];
		g_philo[i].right_fork = &g_fork[i];
		g_philo[i].message = &g_fork[g_info.num_philo];
		i++;
	}
}

int	init_global_var(void)
{
	g_thread = (pthread_t *)malloc(sizeof(pthread_t) * g_info.num_philo);
	if (!g_thread)
		return (0);
	g_philo = (t_philo *)malloc(sizeof(t_philo) * g_info.num_philo);
	if (!g_philo)
		return (0);
	g_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (g_info.num_philo + 1));
	if (!g_fork)
		return (0);
	g_satisfied_philos = 0;
	g_dead_philo = 0;
	g_error = 0;
	return (1);
}

int	find_left_fork(int i)
{
	int	index;

	if (i == 0)
		return (g_info.num_philo - 1);
	else
		return (i - 1);
}

void	parse_info(int ac, char **av)
{
	g_info.num_philo = ft_atoi(av[1]);
	g_info.t_die = ft_atoi(av[2]);
	g_info.time_to_eat = ft_atoi(av[3]);
	g_info.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		g_info.meals_must_eat = ft_atoi(av[5]);
	else
		g_info.meals_must_eat = -1;
}
