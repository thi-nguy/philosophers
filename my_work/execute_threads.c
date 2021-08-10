/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-nguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 09:46:22 by thi-nguy          #+#    #+#             */
/*   Updated: 2021/08/10 10:56:38 by thi-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
void	execute_thread(void)
{
	int	i;

	i = 0;
	while (i < g_info.num_philo)
	{
		if (g_dead_philo == 1)
			return ;
		g_philo[i].t_last_meal = g_t_begin;
		if (pthread_create(&g_thread[i], NULL, routine,
				   (void *)(&g_philo[i])) != 0)
		{
			g_error = 1;
			return ;
		}
		i++;
	}
}

void	*routine(void *arg)
{
	t_philo	*one_philo;

	one_philo = (t_philo *)arg;
	while (1)
	{
		if (g_dead_philo == 1)
			return (0);
		get_both_forks(one_philo);
		philo_eat(get_time(), one_philo);
		if (pthread_mutex_unlock(one_philo->left_fork) == -1
			|| pthread_mutex_unlock(one_philo->right_fork) == -1)
			break ;
		if (g_info.meals_must_eat != -1
			&& one_philo->current_meal == g_info.meals_must_eat)
		{
			g_satisfied_philos++;
			one_philo->is_hungry = 0;
			break ;
		}
		philo_sleep(get_time(), one_philo);
		if (g_dead_philo != 1)
			print_message(get_time() - g_t_begin, one_philo, THINK);
	}
	return (0);
}
