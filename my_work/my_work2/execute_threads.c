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
	// tao 1 thread moi de check tat ca philo
	while (i < info->arg.num_philo)
	{
		//info->philo[i].t_last_meal = 0;
		pthread_create(&info->philo[i].thread, NULL, routine,
				   (void *)(&info->philo[i]));
		i++;
	}
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
	//size_t time_now;

	one_philo = (t_philo *)arg;
	while (*one_philo->global_state == ALIVE)
	{
		//time_now = get_time();
		if (one_philo->state == THINK && *one_philo->global_state != DEAD)
			do_think(one_philo, get_time());
		else if (one_philo->state == FORK && *one_philo->global_state != DEAD)
			*one_philo->forks_taken = take_forks(one_philo);
		else if (one_philo->state == EAT && *one_philo->global_state != DEAD)
			do_eat(one_philo, get_time());
		else if (one_philo->state == SLEEP && *one_philo->global_state != DEAD)
			do_sleep(one_philo, get_time());
	}
	return (NULL);
}
