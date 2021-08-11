/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-nguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 10:10:35 by thi-nguy          #+#    #+#             */
/*   Updated: 2021/08/11 16:32:10 by thi-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	assign_first_fork(t_philo *one_philo)
{
	if (one_philo->index % 2 == 0)
		return (RIGHT);
	else
		return (LEFT);
}

void	get_both_forks(t_philo *one_philo)
{
	if (assign_first_fork(one_philo) == RIGHT)
	{
		get_one_fork(one_philo, RIGHT);
		get_one_fork(one_philo, LEFT);
	}
	else if (assign_first_fork(one_philo) == LEFT)
	{
		get_one_fork(one_philo, LEFT);
		get_one_fork(one_philo, RIGHT);
	}
}

void	get_one_fork(t_philo *one_philo, int which_fork)
{
	if (which_fork == RIGHT)
	{
		if (pthread_mutex_lock(one_philo->right_fork) == -1)
		{
			*one_philo->error = 1;
			return ;
		}
	}
	else
	{
		if (pthread_mutex_lock(one_philo->left_fork) == -1)
		{
			*one_philo->error = 1;
			return ;
		}
	}
	if (*one_philo->is_dead != 1)
		print_message(get_time() - *one_philo->t_start, one_philo, TAKE_A_FORK);
}

void	philo_eat(size_t time_at_beginning_of_eating, t_philo *one_philo)
{
	if (*one_philo->is_dead != 1)
		print_message(time_at_beginning_of_eating - *one_philo->t_start,
			   one_philo, EAT);
	count_time(time_at_beginning_of_eating, one_philo->arg->t_eat);
	one_philo->t_last_meal = get_time();
	one_philo->current_meal++;
}

void	philo_sleep(size_t g_t_begin_of_sleeping, t_philo *one_philo)
{
	if (*one_philo->is_dead != 1)
		print_message(g_t_begin_of_sleeping - *one_philo->t_start, one_philo, SLEEP);
	count_time(g_t_begin_of_sleeping, one_philo->arg->t_sleep);
}
