/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-nguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 09:46:22 by thi-nguy          #+#    #+#             */
/*   Updated: 2021/08/11 16:32:29 by thi-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
void	execute_thread(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->arg.num_philo)
	{
		if (info->is_dead == 1)
			return ;
		info->philo[i].t_last_meal = info->t_start;
		if (pthread_create(&info->philo[i].thread, NULL, routine,
				   (void *)(&info->philo[i])) != 0)
		{
			info->error = 1;
			return ;
		}
		i++;
	}
}

void	*routine(void *arg)
{
	t_philo	*one_philo;

	one_philo = (t_philo *)arg;
	while (*one_philo->is_dead != 1 && *one_philo->satisfied_philo != one_philo->arg->num_philo)
	{
		get_both_forks(one_philo);
		philo_eat(get_time(), one_philo);
		if (pthread_mutex_unlock(one_philo->left_fork) == -1
			|| pthread_mutex_unlock(one_philo->right_fork) == -1)
			break ;
		if (one_philo->current_meal == one_philo->arg->n_meals)
		{
			one_philo->satisfied_philo++;
			break ;
		}
		philo_sleep(get_time(), one_philo);
		if (*one_philo->is_dead != 1)
			print_message(get_time() - *one_philo->t_start, one_philo, THINK);
	}
	return (NULL);
}
