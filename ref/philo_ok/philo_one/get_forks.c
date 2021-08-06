/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 00:21:56 by mkristie          #+#    #+#             */
/*   Updated: 2020/12/03 21:10:04 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	choose_a_fork(t_philo *philo)
{
	if (philo->num % 2 == 0)
		return (RIGHT);
	else
		return (LEFT);
}

static void	get_fork(t_philo *philo, int fork)
{
	if (fork == RIGHT)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	print_message(get_time() - g_start_time, philo->num, \
								TAKEN_A_FORK, philo->message_mutex);
}

void		get_forks(t_philo *philo)
{
	if (choose_a_fork(philo) == RIGHT)
	{
		get_fork(philo, RIGHT);
		get_fork(philo, LEFT);
	}
	else
	{
		get_fork(philo, LEFT);
		get_fork(philo, RIGHT);
	}
}
