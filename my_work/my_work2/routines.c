/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-nguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 10:10:35 by thi-nguy          #+#    #+#             */
/*   Updated: 2021/08/13 23:15:09 by thi-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//! Dat dieu kien take 2 forks cung luc, neu khong drop fork

int		assign_fork(int index)
{
	if (index % 2 == 0)
		return (TAKE_LEFT_FORK);
	return (TAKE_RIGHT_FORK);
}

void	take_forks(t_philo *one_philo)
{
	int 	first_fork;

	first_fork = assign_fork(one_philo->index);
	if (first_fork == TAKE_LEFT_FORK)
	{
		pthread_mutex_lock(one_philo->left_fork);
		pthread_mutex_lock(one_philo->right_fork);
		one_philo->state = EAT;
		return ;
	}
	else if (first_fork == TAKE_RIGHT_FORK)
	{
		pthread_mutex_lock(one_philo->right_fork);
		pthread_mutex_lock(one_philo->left_fork);
		one_philo->state = EAT;
		return ;
	}
}

void	do_eat(t_philo *one_philo)
{
	count_time(get_time(), one_philo->arg->t_eat);
	one_philo->t_last_meal = get_time() - *one_philo->t_start;
	one_philo->current_meal += 1;
	if (one_philo->current_meal == one_philo->arg->n_meals)
	{
		pthread_mutex_lock(one_philo->global_meal);
		*one_philo->satisfied_philo += 1;
		if (*one_philo->satisfied_philo == one_philo->arg->num_philo)
		{
			*one_philo->global_state = STOP;
			return ;
		}
		else
			print_message(one_philo, EAT);
		pthread_mutex_unlock(one_philo->global_meal);
	}
	else
		print_message(one_philo, EAT);
	pthread_mutex_unlock(one_philo->left_fork);
	pthread_mutex_unlock(one_philo->right_fork);
	one_philo->state = SLEEP;
}

void	do_sleep(t_philo *one_philo)
{
	size_t time_now;

	time_now = get_time();
	print_message(one_philo, SLEEP);
	count_time(time_now, one_philo->arg->t_sleep);
	one_philo->state = THINK;
}

void	do_think(t_philo *one_philo)
{
	print_message(one_philo, THINK);
	one_philo->state = FORK;
}

void	die(t_philo *one_philo, size_t time_at_dying)
{
	print_message(one_philo, DEAD);
	*one_philo->global_state = DEAD;
}
