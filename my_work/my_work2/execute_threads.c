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
	while (i < info->arg.num_philo)
	{
		info->philo[i].t_last_meal = 0;
		pthread_create(&info->philo[i].thread, NULL, routine,
				   (void *)(&info->philo[i]));
		i++;
	}
}

void	*routine(void *arg)
{
	t_philo	*one_philo;
	size_t time_now;

	one_philo = (t_philo *)arg;
	while (*one_philo->global_state == ALIVE)
	{
		if (*one_philo->satisfied_philo == one_philo->arg->num_philo)
		{
			*one_philo->global_state = STOP;
			return (NULL);
		}
		if (get_time() - *one_philo->t_start - one_philo->t_last_meal > one_philo->arg->t_die)
		{
			//printf("time last meal of philo %d = %ld\n", one_philo->index, one_philo->t_last_meal);
			die(one_philo, get_time());
			return (NULL);
		}
		time_now = get_time();
		if (one_philo->state == THINK)
			do_think(one_philo, time_now);
		else if (one_philo->state == FORK)
			take_forks(one_philo);
		else if (one_philo->state == EAT)
			do_eat(one_philo, time_now);
		else if (one_philo->state == SLEEP)
			do_sleep(one_philo, time_now);
	}
	return (NULL);
}
