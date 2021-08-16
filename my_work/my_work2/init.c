/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-nguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 09:52:19 by thi-nguy          #+#    #+#             */
/*   Updated: 2021/08/13 23:31:21 by thi-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_info(t_info *info)
{
	int	i;

	info->satisfied_philos = 0;
	info->t_start = get_time();
	info->global_state = ALIVE;
	info->message = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 1);
	if (!info->message)
		return ;
	pthread_mutex_init(info->message, NULL);
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
		pthread_mutex_init(&info->fork[i], NULL);
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
	int right_fork_index;

	info->philo[index].index = index;
	info->philo[index].current_meal = 0;
	info->philo[index].t_last_meal = 0;
	info->philo[index].message = info->message;
	info->philo[index].state = assign_state(index);
	info->philo[index].arg = &info->arg;
	info->philo[index].satisfied_philo = &info->satisfied_philos;
	right_fork_index = find_right_fork(info->arg.num_philo, index);
	info->philo[index].left_fork = &info->fork[index];
	info->philo[index].right_fork = &info->fork[right_fork_index];
	info->philo[index].t_start = &info->t_start;
	info->philo[index].global_state = &info->global_state;
}

int	assign_state(int index)
{
	if (index % 2 == 0)
		return (FORK);
	return (THINK);
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
