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
		if (*one_philo->global_state == ALIVE)
			print_message(get_time() - *one_philo->t_start, one_philo, TAKE_LEFT_FORK);
		pthread_mutex_lock(one_philo->right_fork);
		if (*one_philo->global_state == ALIVE)
			print_message(get_time() - *one_philo->t_start, one_philo, TAKE_RIGHT_FORK);
	}
	else if (first_fork == TAKE_RIGHT_FORK)
	{
		pthread_mutex_lock(one_philo->right_fork);
		if (*one_philo->global_state == ALIVE)
			print_message(get_time() - *one_philo->t_start, one_philo, TAKE_RIGHT_FORK);
		pthread_mutex_lock(one_philo->left_fork);
		if (*one_philo->global_state == ALIVE)
			print_message(get_time() - *one_philo->t_start, one_philo, TAKE_LEFT_FORK);
	}
	one_philo->state = EAT;
}


void	do_eat(t_philo *one_philo, size_t time_to_eat)
{
	if (*one_philo->global_state == ALIVE)
	{
		print_message(time_to_eat - *one_philo->t_start,
				one_philo, EAT);
	}
	count_time(time_to_eat, one_philo->arg->t_eat);
	one_philo->t_last_meal = get_time() - *one_philo->t_start;
	if (one_philo->arg->n_meals != -1 && one_philo->current_meal == one_philo->arg->n_meals)
		one_philo->satisfied_philo++;
	one_philo->state = SLEEP;
	one_philo->current_meal++;
	if (*one_philo->global_state == ALIVE)
	{
		print_message(get_time() - *one_philo->t_start, one_philo, TAKE_DOWN_LEFT_FORK);
	}
	if (*one_philo->global_state == ALIVE)
	{
		print_message(get_time() - *one_philo->t_start, one_philo, TAKE_DOWN_RIGHT_FORK);
	}
}

void	do_sleep(t_philo *one_philo, size_t time_at_beginning_of_sleeping)
{
	if (*one_philo->global_state == ALIVE)
		print_message(time_at_beginning_of_sleeping - *one_philo->t_start, one_philo, SLEEP);
	count_time(time_at_beginning_of_sleeping, one_philo->arg->t_sleep);
	one_philo->state = THINK;
}

void	do_think(t_philo *one_philo, size_t time_at_beginning_of_thinking)
{
	if (*one_philo->global_state == ALIVE)
		print_message(time_at_beginning_of_thinking - *one_philo->t_start, one_philo, THINK);
	one_philo->state = FORK;
}

void	die(t_philo *one_philo, size_t time_at_dying)
{
	print_message(time_at_dying - *one_philo->t_start, one_philo, DEAD);
	*one_philo->global_state = DEAD;
}
