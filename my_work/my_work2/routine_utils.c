/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-nguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 10:08:31 by thi-nguy          #+#    #+#             */
/*   Updated: 2021/08/13 18:45:24 by thi-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

const char	*get_action_name(int action)
{
	if (action == TAKE_RIGHT_FORK)
		return ("taking right fork");
	else if (action == TAKE_LEFT_FORK)
		return ("taking left fork");
	else if (action == TAKE_DOWN_RIGHT_FORK)
		return ("taking down right fork");
	else if (action == TAKE_DOWN_LEFT_FORK)
		return ("taking down left fork");
	else if (action == SLEEP)
		return ("sleeping");
	else if (action == EAT)
		return ("eating");
	else if (action == THINK)
		return ("thinking");
	else if (action == DEAD)
		return ("dead");
	else
		return (NULL);
}

void	create_message(size_t time, t_philo *one_philo, int action)
{
	char	*action_name;

	action_name = ft_strdup(get_action_name(action));
	printf("%zu %d is %s\n", time, one_philo->index, action_name);
	free(action_name);
	action_name = NULL;
}

void	print_message(size_t time, t_philo *one_philo, int action)
{
	pthread_mutex_lock(one_philo->message);
	create_message(time, one_philo, action);
	if (action != DEAD)
		pthread_mutex_unlock(one_philo->message);
}

void	count_time(size_t time, size_t desired_time)
{
	while (get_time() - time < desired_time)
		usleep(10);
}
