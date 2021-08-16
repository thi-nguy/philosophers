/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-nguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 09:55:15 by thi-nguy          #+#    #+#             */
/*   Updated: 2021/08/12 21:31:22 by thi-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	int	i;
	t_info info;

	if (check_arg(ac, av) == -1)
		return (0);
	parse_info(ac, av, &info);
	init_info(&info);
	execute_thread(&info);
	// TODO; join thread, destroy mutex, free memory
	end_simulation(&info);
	return (0);
}

void	end_simulation(t_info *info)
{
	int	i;

	pthread_join(info->global_thread, NULL);
	i = 0;
	while (i < info->arg.num_philo)
	{
		pthread_join(info->philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < info->arg.num_philo)
	{
		pthread_mutex_destroy(&info->fork[i]);
		i++;
	}
	pthread_mutex_destroy(info->message);

	free_memory(info);
}

void	free_memory(t_info *info)
{
	int	i;

	if (info->message)
	{
		free(info->message);
		info->message = NULL;
	}
	if (info->philo)
	{
		free(info->philo);
		info->philo = NULL;
	}
	if (info->fork)
	{
		free(info->fork);
		info->fork = NULL;
	}
}
