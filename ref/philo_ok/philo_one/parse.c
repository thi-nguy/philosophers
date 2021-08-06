/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:21:11 by mkristie          #+#    #+#             */
/*   Updated: 2020/12/01 19:21:12 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

_Bool	parse_args(int ac, char **av, t_input *input)
{
	input->n_philos = ft_atoi(av[1]);
	input->time_to_die = ft_atoi(av[2]);
	input->time_to_eat = ft_atoi(av[3]);
	input->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		input->desired_meals = ft_atoi(av[5]);
		g_full_philos = input->desired_meals;
	}
	else
		input->desired_meals = 0;
	if (input->n_philos < 2 || input->time_to_die <= 0 || \
		input->time_to_eat <= 0 || input->time_to_sleep <= 0 || \
		(ac == 6 && input->desired_meals < 1))
		return (1);
	return (0);
}

_Bool	parse(int ac, char **av, t_input *input)
{
	if ((ac != 5 && ac != 6) || is_bad_input(av))
	{
		ft_putstr_fd("error arguments count or bad content", 2);
		return (1);
	}
	if (parse_args(ac, av, input) || init_input(*input))
	{
		ft_putstr_fd("out of memory", 2);
		return (1);
	}
	return (0);
}
