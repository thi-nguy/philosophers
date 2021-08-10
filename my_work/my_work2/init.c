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

void	init_info(t_info *info)
{
	int	i;

	info->is_dead = 0;
	info->satisfied_philos = 0;
	info->error = 0;
	info->t_start = get_time();
	info->message = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* 1);
	if (!info->message)
		return ;
	if (pthread_mutex_init(info->message, NULL))
	{
		info->error = 1;
		return ;
	}
	init_fork(info);
	init_philo(info);
}

void	init_fork(t_info *info)
{
	int i;

	info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->arg.num_philo);
	if (!info->fork)
		return ;
	i = 0;
	while (i < info->arg.num_philo)
	{
		if (pthread_mutex_init(&info->fork[i], NULL))
		{
			info->error = 1;
			break ;
		}
		i++;
	}
}

void	init_philo(t_info *info)
{
	int i;

	info->philo = (t_philo *)malloc(sizeof(t_philo) * info->arg.num_philo);
	if (!info->philo)
		return ;
	i = 0;
	while (i < info->arg.num_philo)
	{
		init_one_philo(info, i);
		i++;
	}
}

void	init_one_philo(t_info *info, int index)
{
	int left_fork_index;

	info->philo->index = index;
	info->philo->current_meal = 0;
	info->philo->is_dead = 0;
	info->philo->is_hungry = 1;
	left_fork_index = find_left_fork(info->arg.num_philo, index);
	info->philo->left_fork = &info->fork[left_fork_index];
	info->philo->right_fork = &info->fork[index];
}


void	parse_info(int ac, char **av, t_info *info)
{
	info->arg.num_philo = ft_atoi(av[1]);
	info->arg.t_die = ft_atoi(av[2]);
	info->arg.t_eat = ft_atoi(av[3]);
	info->arg.t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->arg.n_meals = ft_atoi(av[5]);
	else
		info->arg.n_meals = -1;
}
