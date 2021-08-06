/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:21:20 by mkristie          #+#    #+#             */
/*   Updated: 2020/12/03 21:05:38 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

_Bool		init_input(t_input input)
{
	if (!(g_philos = malloc(sizeof(t_philo) * input.n_philos)))
		return (1);
	if (!(g_forks = malloc(sizeof(pthread_mutex_t) * input.n_philos + 1)))
	{
		free(g_philos);
		return (1);
	}
	if (!(g_philo_threads = malloc(sizeof(pthread_t) * input.n_philos)))
	{
		free(g_philos);
		free(g_forks);
		return (1);
	}
	return (0);
}

int			assign_left_fork(int i, int num)
{
	int		j;

	j = i == 0 ? num - 1 : i - 1;
	return (j);
}

int			assign_right_fork(int i)
{
	int		j;

	j = i == 0 ? 0 : i;
	return (j);
}

void		init_philo(t_input input)
{
	int	i;

	i = 0;
	while (i < input.n_philos)
	{
		g_philos[i].num = i;
		g_philos[i].time_to_die = input.time_to_die;
		g_philos[i].time_to_eat = input.time_to_eat;
		g_philos[i].time_to_sleep = input.time_to_sleep;
		g_philos[i].desired_meals = input.desired_meals;
		g_philos[i].current_meal = 0;
		g_philos[i].is_hungry = 1;
		g_philos[i].left_fork = &g_forks[assign_left_fork(i, input.n_philos)];
		g_philos[i].right_fork = &g_forks[assign_right_fork(i)];
		g_philos[i].message_mutex = &g_forks[input.n_philos];
		i++;
	}
}

void		init_forks(int number_of_forks)
{
	int	i;

	i = 0;
	while (i < number_of_forks + 1)
	{
		pthread_mutex_init(&g_forks[i], NULL);
		i++;
	}
}
