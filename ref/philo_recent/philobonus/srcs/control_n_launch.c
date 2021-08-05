/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_n_launch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tefroiss <tefroiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 15:16:34 by tefroiss          #+#    #+#             */
/*   Updated: 2021/07/15 11:51:25 by tefroiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	del_philo_th(t_table *table)
{
	int	i;

	if (table)
	{
		i = 0;
		while (i < table->args.n_philo)
		{
			kill(table->philo[i].fork_philo, SIGKILL);
			i++;
		}
	}
}

void	create_phi_fork(t_philo *philo, t_table *table)
{
	philo->fork_philo = fork();
	if (philo->fork_philo == 0)
		go_phiphi(philo);
	else if (philo->fork_philo < 0)
	{
		printf("ERROR:\nFORK FAILED\n");
		del_philo_th(table);
		its_the_end(table);
		exit(-1);
	}
}

void	launch_engine(t_table *table)
{
	int	i;

	if (table)
	{
		i = 0;
		while (i < table->args.n_philo)
		{
			create_phi_fork(&table->philo[i], table);
			i++;
		}
	}
}
