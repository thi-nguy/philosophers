/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-nguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 09:55:15 by thi-nguy          #+#    #+#             */
/*   Updated: 2021/08/11 16:48:27 by thi-nguy         ###   ########.fr       */
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
	if (stop_simulation(&info) == 1)
		//TODO; join thread, destroy mutex, free memory 
		end_simulation(&info); 
	return (0);
}

int	stop_simulation(t_info *info)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < info->arg.num_philo)
		{
			if (info->is_dead == 1)
			{
				print_message(get_time() - info->t_start, &info->philo[i], DEAD);
				return (1);
			}
			// if (g_satisfied_philos == g_info.num_philo)
			// 	return (1);
		}

	}
	return (0);
}

void	end_simulation(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->arg.num_philo)
	{
		pthread_join(info->philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < info->arg.num_philo)
	{
		pthread_mutex_destroy(info->philo[i].left_fork);
		pthread_mutex_destroy(info->philo[i].right_fork);
		i++;
	}
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
