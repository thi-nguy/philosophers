/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:21:20 by mkristie          #+#    #+#             */
/*   Updated: 2020/12/04 22:31:13 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

_Bool		init_input(t_input input)
{
	if (!(g_philos = malloc(sizeof(t_philo) * input.n_philos)))
		return (1);
	if (!(g_philo_threads = malloc(sizeof(pthread_t) * input.n_philos)))
	{
		free(g_philos);
		return (1);
	}
	return (0);
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
		i++;
	}
}

_Bool		init_forks(int size)
{
	sem_unlink("/g_forks");
	if ((g_forks = sem_open("/g_forks", O_CREAT, S_IRWXU, size)) == SEM_FAILED)
		return (1);
	sem_unlink("/g_message_sem");
	if ((g_message_sem = sem_open("/g_message_sem", O_CREAT, S_IRWXU, 1)) \
																== SEM_FAILED)
		return (1);
	return (0);
}
