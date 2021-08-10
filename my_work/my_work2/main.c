/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-nguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 09:55:15 by thi-nguy          #+#    #+#             */
/*   Updated: 2021/08/10 11:32:02 by thi-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	int	i;
	t_info info;

	if (check_arg(ac, av) == -1)
		return (0);
	parse_info(ac, av, &info);
	init_info(&info);
	//execute_thread();
	//if (stop_simulation())
	//{
	//	wait_threads();
	//	free_memory();
	//	return (0);
	//}
	return (0);
}

//int	stop_simulation(void)
//{
//	int	i;

//	while (1)
//	{
//		i = -1;
//		while (++i < g_info.num_philo)
//		{
//			if (g_dead_philo || g_error)
//				return (1);
//			if (get_time() - g_philo[i].t_last_meal > g_info.t_die
//				|| (g_philo[i].is_hungry && get_time()
//					- g_philo[i].t_last_meal > g_info.t_die))
//			{
//				print_message(get_time() - g_t_begin, &g_philo[i], DEAD);
//				g_dead_philo = 1;
//				return (1);
//			}
//			if (g_satisfied_philos == g_info.num_philo)
//				return (1);
//		}
//	}
//	return (0);
//}

//void	wait_threads(void)
//{
//	int	i;

//	i = 0;
//	while (i < g_info.num_philo)
//	{
//		pthread_join(g_thread[i], NULL);
//		i++;
//	}
//}

//void	free_memory(void)
//{
//	if (g_philo)
//	{
//		free(g_philo);
//		g_philo = NULL;
//	}
//	if (g_fork)
//	{
//		free(g_fork);
//		g_fork = NULL;
//	}
//	if (g_thread)
//	{
//		free(g_thread);
//		g_thread = NULL;
//	}
//}
