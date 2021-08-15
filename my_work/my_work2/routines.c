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

int	take_forks(t_philo *one_philo)
{
	int forks;

	forks = 0;
	if (pthread_mutex_lock(one_philo->left_fork) == 0)
	{
		print_message(get_time() - *one_philo->t_start, one_philo, TAKE_LEFT_FORK);
		forks++;

	}
	if (pthread_mutex_lock(one_philo->right_fork) == 0)
	{
		print_message(get_time() - *one_philo->t_start, one_philo, TAKE_RIGHT_FORK);
		forks++;
	}
	//*one_philo->forks_taken = forks;
	one_philo->state = EAT;
	return (forks);
}


void	do_eat(t_philo *one_philo, size_t time_to_eat)
{
	int forks;

	forks = *one_philo->forks_taken;
	print_message(time_to_eat - *one_philo->t_start,
			   one_philo, EAT);
	count_time(time_to_eat, one_philo->arg->t_eat);
	one_philo->t_last_meal = get_time() - *one_philo->t_start;
	//printf("Time stamp last meal for philo %d: %ld\n", one_philo->index, one_philo->t_last_meal);
	if (one_philo->arg->n_meals != -1 && one_philo->current_meal == one_philo->arg->n_meals)
		one_philo->satisfied_philo++;
	one_philo->state = SLEEP;
	one_philo->current_meal++;
	if (pthread_mutex_unlock(one_philo->left_fork) == 0)
	{
		print_message(get_time() - *one_philo->t_start, one_philo, TAKE_DOWN_LEFT_FORK);
		forks--;
	}
	if (pthread_mutex_unlock(one_philo->right_fork) == 0)
	{
		print_message(get_time() - *one_philo->t_start, one_philo, TAKE_DOWN_RIGHT_FORK);
		forks--;
	}
	*one_philo->forks_taken = forks;
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
	//while (*one_philo->forks_taken == 2)
	//	usleep(100);
	one_philo->state = FORK;
}

void	die(t_philo *one_philo, size_t time_at_dying)
{
	print_message(time_at_dying - *one_philo->t_start, one_philo, DEAD);
	*one_philo->global_state = DEAD;
}
