/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_repeat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:25:22 by mkristie          #+#    #+#             */
/*   Updated: 2020/12/04 20:53:09 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		count_time(size_t time, size_t desired_time)
{
	while (get_time() - time < desired_time)
		usleep(100);
}

void		eat(size_t eating_time, t_philo *philo)
{
	print_message(eating_time - g_start_time, \
					philo->num, EAT, philo->message_mutex);
	count_time(eating_time, philo->time_to_eat);
	philo->last_meal_time = get_time();
	philo->current_meal++;
}

void		sleep_philo(size_t sleeping_time, t_philo *philo)
{
	print_message(sleeping_time - g_start_time, philo->num, \
									SLEEP, philo->message_mutex);
	count_time(sleeping_time, philo->time_to_sleep);
}

void		*eat_sleep_repeat(void *val)
{
	t_philo *philo;

	philo = (t_philo *)val;
	while (1)
	{
		get_forks(philo);
		eat(get_time(), philo);
		if (pthread_mutex_unlock(philo->left_fork) || \
			pthread_mutex_unlock(philo->right_fork))
		{
			g_error = FATAL_ERR;
			break ;
		}
		if (philo->desired_meals && philo->current_meal == philo->desired_meals)
		{
			g_full_philos++;
			philo->is_hungry = 0;
			break ;
		}
		sleep_philo(get_time(), philo);
		print_message(get_time() - g_start_time, philo->num, \
										THINK, philo->message_mutex);
	}
	return (0);
}
