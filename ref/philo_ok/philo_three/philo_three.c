/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:21:14 by mkristie          #+#    #+#             */
/*   Updated: 2020/12/05 00:30:29 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

t_philo			*g_philo;
sem_t			*g_forks;
sem_t			*g_message_sem;
size_t			g_start_time;

_Bool			monitor(void)
{
	int			full;
	int			status;
	int			ret;
	int			i;

	full = 0;
	i = -1;
	while (1)
	{
		waitpid(-1, &status, 0);
		ret = WEXITSTATUS(status);
		if (ret == FULL)
			full++;
		else if (ret == DEATH)
		{
			while (++i < g_philo->n_philos)
				kill(g_philo->pid[i], SIGKILL);
			exit(0);
		}
		if (full == g_philo->n_philos)
			return (0);
	}
	return (0);
}

void			free_all_mem(void)
{
	if (g_philo)
	{
		free(g_philo->pid);
		free(g_philo);
	}
	if (sem_unlink("/g_forks") == -1 || sem_close(g_forks) == -1)
		error_fatal();
	if (sem_unlink("/g_message_sem") == -1 || sem_close(g_message_sem) == -1)
		error_fatal();
}

void			*monitor_process(void *val)
{
	t_philo		*philo;

	philo = (t_philo *)val;
	while (1)
	{
		usleep(21);
		if (get_time() - philo->last_meal_time > philo->time_to_die)
		{
			print_message(get_time() - g_start_time, philo->num, DEATH);
			exit(DEATH);
		}
	}
}

int				main(int ac, char **av)
{
	int			i;

	if (parse(ac, av) || init_semaphors(g_philo->n_philos))
		return (1);
	i = 0;
	g_start_time = get_time();
	while (i < g_philo->n_philos)
	{
		g_philo->num = i;
		g_philo->last_meal_time = g_start_time;
		g_philo->pid[i] = fork();
		if (g_philo->pid[i] < 0)
			error_fatal();
		else if (g_philo->pid[i] == 0)
		{
			pthread_create(&g_philo->thread, NULL, \
						monitor_process, (void *)g_philo);
			eat_sleep_repeat();
			exit(0);
		}
		i++;
	}
	if (monitor())
		free_all_mem();
	return (0);
}
