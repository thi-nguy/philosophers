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

void	take_forks(t_philo *one_philo, size_t time_at_taking_fork)
{
	get_both_forks(one_philo, time_at_taking_fork);
	if (one_philo->fork_take == 2)
		one_philo->state = EAT;
}

void	get_both_forks(t_philo *one_philo, size_t time)
{
	pthread_t	thread;

	if (pthread_mutex_lock(one_philo->right_fork) != -1)
	{
		print_message(time - *one_philo->t_start, one_philo, TAKE_RIGHT_FORK);
		one_philo->fork_take++;
		one_philo->right_fork_take = 1;
	}
	if (pthread_mutex_lock(one_philo->left_fork) != -1)
	{
		print_message(time - *one_philo->t_start, one_philo, TAKE_LEFT_FORK);
		one_philo->fork_take++;
		one_philo->left_fork_take = 1;
	}
}

void	do_eat(t_philo *one_philo, size_t time_to_eat)
{
	print_message(time_to_eat - *one_philo->t_start,
			   one_philo, EAT);
	count_time(time_to_eat, one_philo->arg->t_eat);
	one_philo->t_last_meal = time_to_eat - *one_philo->t_start + one_philo->arg->t_eat;
	if (pthread_mutex_unlock(one_philo->left_fork) != -1)
	{
		print_message(get_time() - *one_philo->t_start, one_philo, TAKE_DOWN_LEFT_FORK);
		one_philo->fork_take--;
		one_philo->left_fork_take = 0;
	}
	if (pthread_mutex_unlock(one_philo->right_fork) != -1)
	{
		print_message(get_time() - *one_philo->t_start, one_philo, TAKE_DOWN_RIGHT_FORK);
		one_philo->fork_take--;
		one_philo->right_fork_take = 0;
	}
	one_philo->current_meal++;
	if (one_philo->current_meal == one_philo->arg->n_meals)
		*one_philo->satisfied_philo++;
	one_philo->state = SLEEP;
}

void	do_sleep(t_philo *one_philo, size_t time_at_beginning_of_sleeping)
{
	print_message(time_at_beginning_of_sleeping - *one_philo->t_start, one_philo, SLEEP);
	count_time(time_at_beginning_of_sleeping, one_philo->arg->t_sleep);
	one_philo->state = THINK;
}

void	do_think(t_philo *one_philo, size_t time_at_beginning_of_thinking)
{
	print_message(time_at_beginning_of_thinking - *one_philo->t_start, one_philo, THINK);
	if (one_philo->fork_take != 2)
	{
		
		if (one_philo->right_fork_take == 1)
		{
			pthread_mutex_unlock(one_philo->right_fork);
			print_message(get_time() - *one_philo->t_start, one_philo, TAKE_DOWN_RIGHT_FORK);
			one_philo->fork_take--;
			one_philo->right_fork_take = 0;

		}
		if (one_philo->left_fork_take == 1)
		{
			pthread_mutex_unlock(one_philo->left_fork);
			print_message(get_time() - *one_philo->t_start, one_philo, TAKE_DOWN_LEFT_FORK);
			one_philo->fork_take--;
			one_philo->left_fork_take = 0;
		}
		// count_time(time_at_beginning_of_thinking, one_philo->arg->t_eat);
	}
	one_philo->state = TAKE_RIGHT_FORK;
}

void	die(t_philo *one_philo, size_t time_at_dying)
{
	print_message(time_at_dying - *one_philo->t_start, one_philo, DEAD);
	*one_philo->global_state = DEAD;
}