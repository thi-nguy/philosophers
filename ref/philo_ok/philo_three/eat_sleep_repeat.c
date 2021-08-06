/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_repeat.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:25:22 by mkristie          #+#    #+#             */
/*   Updated: 2020/12/02 02:10:53 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		count_time(size_t time, size_t desired_time)
{
	while (get_time() - time < desired_time)
		usleep(100);
}

void		eat(size_t eating_time, t_philo *philo)
{
	print_message(eating_time - g_start_time, philo->num, EAT);
	count_time(eating_time, philo->time_to_eat);
	philo->last_meal_time = get_time();
	philo->current_meal++;
}

void		sleep_philo(size_t sleeping_time, t_philo *philo)
{
	print_message(sleeping_time - g_start_time, philo->num, SLEEP);
	count_time(sleeping_time, philo->time_to_sleep);
}

void		*eat_sleep_repeat(void)
{
	t_philo *philo;

	philo = g_philo;
	while (1)
	{
		sem_wait(g_forks);
		print_message(get_time() - g_start_time, philo->num, TAKEN_A_FORK);
		sem_wait(g_forks);
		print_message(get_time() - g_start_time, philo->num, TAKEN_A_FORK);
		eat(get_time(), philo);
		sem_post(g_forks);
		sem_post(g_forks);
		if (philo->desired_meals && philo->current_meal == philo->desired_meals)
			exit(FULL);
		sleep_philo(get_time(), philo);
		print_message(get_time() - g_start_time, philo->num, THINK);
	}
	return (0);
}
