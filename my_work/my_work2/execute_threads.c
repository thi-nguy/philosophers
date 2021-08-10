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
				   (void *)(&info)) != 0)
		{
			info->error = 1;
			return ;
		}
		i++;
	}
}

//void	*routine(void *arg)
//{
//	t_info	*one_philo;

//	one_philo = (t_info *)arg;
//	while (1)
//	{
//		if (one_philo->is_dead == 1)
//			return (0);
//		get_both_forks(one_philo);
//		philo_eat(get_time(), one_philo);
//		if (pthread_mutex_unlock(one_philo->left_fork) == -1
//			|| pthread_mutex_unlock(one_philo->right_fork) == -1)
//			break ;
//		if (g_info.n_meals != -1
//			&& one_philo->current_meal == g_info.n_meals)
//		{
//			g_satisfied_philos++;
//			one_philo->is_hungry = 0;
//			break ;
//		}
//		philo_sleep(get_time(), one_philo);
//		if (g_dead_philo != 1)
//			print_message(get_time() - g_t_begin, one_philo, THINK);
//	}
//	return (0);
//}
