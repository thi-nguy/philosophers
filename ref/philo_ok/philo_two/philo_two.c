/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:21:14 by mkristie          #+#    #+#             */
/*   Updated: 2020/12/04 23:03:45 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

t_philo			*g_philos;
sem_t			*g_forks;
sem_t			*g_message_sem;
pthread_t		*g_philo_threads;
size_t			g_start_time;
int				g_full_philos;
int				g_error;

_Bool			monitor(t_input input)
{
	int i;

	while (1)
	{
		i = 0;
		while (i < input.n_philos)
		{
			if (g_philos[i].is_hungry && \
			get_time() - g_philos[i].last_meal_time > g_philos[i].time_to_die)
			{
				print_message(get_time() - g_start_time, i, DEATH);
				return (1);
			}
			if (g_full_philos && g_full_philos == input.n_philos)
				return (1);
			i++;
		}
		if (g_error == FATAL_ERR)
		{
			ft_putstr_fd("error: fatal\n", 2);
			return (1);
		}
	}
	return (0);
}

_Bool			free_all_mem(int size)
{
	int			i;

	i = 0;
	while (i < size)
	{
		if (pthread_detach(g_philo_threads[i]))
		{
			g_error = FATAL_ERR;
			break ;
		}
		i++;
	}
	if (g_philos)
		free(g_philos);
	if (g_philo_threads)
		free(g_philo_threads);
	if (sem_unlink("/g_forks") == -1)
		g_error = FATAL_ERR;
	if (sem_unlink("/g_message_sem") == -1 || sem_close(g_message_sem) == -1)
		g_error = FATAL_ERR;
	if (g_error)
		return (1);
	return (0);
}

int				main(int ac, char **av)
{
	t_input		input;
	int			i;

	if (parse(ac, av, &input))
		return (1);
	init_philo(input);
	init_forks(input.n_philos);
	i = 0;
	g_full_philos = 0;
	while (i < input.n_philos)
	{
		g_start_time = get_time();
		g_philos[i].last_meal_time = g_start_time;
		pthread_create(&g_philo_threads[i], NULL, \
							eat_sleep_repeat, (void *)(&g_philos[i]));
		i++;
		usleep(10);
	}
	if (monitor(input))
		if (free_all_mem(input.n_philos))
			return (1);
	return (0);
}
