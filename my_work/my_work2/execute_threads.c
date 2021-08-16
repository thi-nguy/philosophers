/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-nguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 09:46:22 by thi-nguy          #+#    #+#             */
/*   Updated: 2021/08/13 23:27:44 by thi-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
void	execute_thread(t_info *info)
{
	int	i;

	i = 0;
	pthread_create(&info->global_thread, NULL, check_status, (void *)(info));
	while (i < info->arg.num_philo)
	{
		pthread_create(&info->philo[i].thread, NULL, routine,
				   (void *)(&info->philo[i]));
		i++;
	}
	pthread_join(info->global_thread, NULL);
}

void	*check_status(void *arg)
{
	t_info 		*info;
	int i;

	info = (t_info *)arg;
	while (1)
	{
		if (info->satisfied_philos == info->arg.num_philo)
		{
			info->global_state = STOP;
			return (NULL);
		}
		i = 0;
		while (i < info->arg.num_philo)
		{
			if (get_time() - info->t_start - info->philo[i].t_last_meal > info->arg.t_die)
			{
				die(&info->philo[i], get_time());
				return (NULL);
			}
			i++;
		}
	}
}

void	*routine(void *arg)
{
	t_philo	*one_philo;

	one_philo = (t_philo *)arg;
	while (*one_philo->global_state == ALIVE)
	{
		if (one_philo->state == THINK)
			do_think(one_philo, get_time());
		else if (one_philo->state == FORK)
			take_forks(one_philo);
		else if (one_philo->state == EAT)
			do_eat(one_philo, get_time());
		else if (one_philo->state == SLEEP)
			do_sleep(one_philo, get_time());
	}
	return (NULL);
}
