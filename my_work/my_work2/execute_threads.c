/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-nguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 09:46:22 by thi-nguy          #+#    #+#             */
/*   Updated: 2021/08/12 22:44:16 by thi-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	execute_thread(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->arg.num_philo)
	{
		pthread_create(&info->philo[i].thread, NULL, routine,
				   (void *)(&info->philo[i]));
		i++;
	}
}

void	*routine(void *arg)
{
	t_philo	*one_philo;
	size_t time_now;

	one_philo = (t_philo *)arg;
	while (one_philo->state != DEAD && one_philo->state != STOP)
	{
		
		// TODO: condition to die. If not die, continue
		// TODO: if die, print message, return.
			// TODO Condition 1: no one has eaten.
			// TODO Condition 2: time pass the time_to_die
		time_now = get_time();
		if (*one_philo->satisfied_philo == one_philo->arg->num_philo)
		{
			one_philo->state = STOP;
			break ;
		}
		if (time_now - *one_philo->t_start - one_philo->t_last_meal > one_philo->arg->t_die)
		{
			printf("time last meal of philo %d = %ld\n", one_philo->index, one_philo->t_last_meal);
			die(one_philo, time_now);
			break ;
		}
		if (one_philo->state == EAT)
			do_eat(one_philo, time_now);
		else if (one_philo->state == TAKE_A_FORK)
			take_forks(one_philo, time_now);
		else if (one_philo->state == SLEEP)
			do_sleep(one_philo, time_now);
		else if (one_philo->state == THINK)
			do_think(one_philo, time_now);
	}
	pthread_mutex_unlock(one_philo->left_fork);
	pthread_mutex_unlock(one_philo->right_fork);
	return (NULL);
}

// void philo_do_something(t_philo *one_philo, void (*ph_action)(t_philo *, size_t))
// {
// 		size_t	time_now;
		
// 		time_now = get_time();
// 		if (*one_philo->satisfied_philo == one_philo->arg->num_philo)
// 		{
// 			one_philo->state = STOP;
// 			return ;
// 		}
// 		if (time_now - *one_philo->t_start - one_philo->t_last_meal > one_philo->arg->t_die)
// 		{
// 			printf("time last meal of philo %d = %ld\n", one_philo->index, one_philo->t_last_meal);
// 			die(one_philo, time_now);
// 			return ;
// 		}
// 		ph_action(one_philo, time_now);
// }