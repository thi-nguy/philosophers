/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_mac.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 12:12:46 by tefroiss          #+#    #+#             */
/*   Updated: 2021/07/15 11:51:25 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	its_the_end(t_table *table)
{
	if (table && table->philo)
	{
		free(table->philo);
		sem_close(table->fork);
		sem_unlink("fork");
	}
	sem_close(table->lock_output);
	sem_unlink("lock_output");
}

void	philo_pass_away(t_philo *philo, t_state status)
{
	int	timestamp;

	philo->status = status;
	sem_wait(philo->lock_output);
	timestamp = get_timestamp(philo);
	if (*philo->alive)
	{
		if (philo->status == DIED)
		{
			printf("%d ... Philo %u ... %s", timestamp, philo->index, \
				"sadly DEAD... Rip in peace.\n");
			*philo->alive = FALSE;
			exit(1);
		}
		else if (philo->status == STOP)
		{
			printf("%d ... Philo %u ... %s", timestamp, philo->index, \
				"STOP everything. I'm not Gargantua. Just a Philo !\n");
			sem_post(philo->lock_output);
			exit(0);
		}
	}
}

void	control_the_mind(t_table *table)
{
	int	signal;

	signal = 0;
	while (!signal)
	{
		if (waitpid(-1, &signal, 0) <= 0)
			break ;
	}
	del_philo_th(table);
	its_the_end(table);
}
