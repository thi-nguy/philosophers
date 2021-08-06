/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:21:11 by mkristie          #+#    #+#             */
/*   Updated: 2020/12/05 00:29:32 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

_Bool	is_bad_input(char **av)
{
	int i;
	int j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

_Bool	init_input(void)
{
	if (!(g_philo->pid = malloc(sizeof(pid_t) * (g_philo->n_philos))))
	{
		free(g_philo);
		return (1);
	}
	return (0);
}

_Bool	parse_args(int ac, char **av)
{
	if (!(g_philo = malloc(sizeof(t_philo))))
		return (1);
	g_philo->n_philos = ft_atoi(av[1]);
	g_philo->time_to_die = ft_atoi(av[2]);
	g_philo->time_to_eat = ft_atoi(av[3]);
	g_philo->time_to_sleep = ft_atoi(av[4]);
	g_philo->is_hungry = 0;
	if (ac == 6)
	{
		g_philo->desired_meals = ft_atoi(av[5]);
	}
	else
		g_philo->desired_meals = 0;
	if (g_philo->n_philos < 2 || g_philo->time_to_die <= 0 || \
		g_philo->time_to_eat <= 0 || g_philo->time_to_sleep <= 0 || \
		(ac == 6 && g_philo->desired_meals < 1))
		return (1);
	return (0);
}

_Bool	parse(int ac, char **av)
{
	if ((ac != 5 && ac != 6) || is_bad_input(av))
	{
		ft_putstr_fd("error arguments count or bad content", 2);
		return (1);
	}
	if (parse_args(ac, av) || init_input())
	{
		ft_putstr_fd("out of memory", 2);
		return (1);
	}
	return (0);
}
