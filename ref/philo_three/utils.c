/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 22:15:40 by user42            #+#    #+#             */
/*   Updated: 2020/07/27 21:28:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	simulation_delete(void *t1)
{
	unsigned int	i;
	char			*semkey;

	i = 0;
	while (i < g_s.n)
	{
		semkey = ft_strjoin_free("eating_", ft_itoa(i), 2);
		g_eating = sem_open(semkey, O_CREAT, S_IRWXU, 1);
		sem_unlink(semkey);
		sem_close(g_eating);
		free(semkey);
		i++;
	}
	free(t1);
	sem_unlink(SEMFORKS);
	sem_close(g_forks);
	sem_unlink(SEMDEATH);
	sem_close(g_death);
	sem_unlink(SEMMEALS);
	sem_close(g_meals);
}

int		simulation_init(t_simulation_data *sim, int ac, char **av)
{
	pthread_t tid;

	simulation_delete(NULL);
	if (ac < 5 || (sim->n = ft_atoi(av[1])) > THREADS_MAX)
	{
		write(1, USAGE, ft_strlen(USAGE));
		return (1);
	}
	sim->time_to_die = ft_atoi(av[2]);
	sim->time_to_eat = ft_atoi(av[3]);
	sim->time_to_sleep = ft_atoi(av[4]);
	sim->meals_option = ac > 5 ? ft_atoi(av[5]) : 0;
	if ((g_forks = sem_open(SEMFORKS, O_CREAT, S_IRWXU, sim->n)) == SEM_FAILED
		|| (g_death = sem_open(SEMDEATH, O_CREAT, S_IRWXU, 0)) == SEM_FAILED
		|| (g_meals = sem_open(SEMMEALS, O_CREAT, S_IRWXU, 0)) == SEM_FAILED)
		return (1);
	gettimeofday(&(sim->start), NULL);
	if (sim->meals_option > 0)
		pthread_create(&tid, NULL, count_meals_routine, NULL);
	return (0);
}

int		*create_childs(unsigned int n)
{
	int				*pids;
	unsigned int	i;

	if ((pids = malloc(sizeof(int) * n)) == NULL)
		return (NULL);
	i = -1;
	while (++i < n)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			child_process_actions(i + 1);
			return (NULL);
		}
	}
	return (pids);
}

void	child_process_actions(unsigned int n)
{
	pthread_t		tid;
	struct timeval	now;
	char			*semkey;

	semkey = ft_strjoin_free("eating_", ft_itoa(n - 1), 2);
	sem_unlink(semkey);
	if ((g_eating = sem_open(semkey, O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		exit(EXIT_FAILURE);
	free(semkey);
	pthread_create(&tid, NULL, philosophing, &n);
	gettimeofday(&g_last_meal, NULL);
	while (TRUE)
	{
		sem_wait(g_eating);
		gettimeofday(&now, NULL);
		if (elapsed_time(g_last_meal, now) > g_s.time_to_die)
		{
			message(n, DEAD);
			sem_post(g_eating);
			sem_post(g_death);
			return ;
		}
		sem_post(g_eating);
		ft_sleep(5);
	}
}

void	*count_meals_routine(void *arg)
{
	unsigned int	i;

	(void)arg;
	i = 0;
	while (i < g_s.n)
	{
		sem_wait(g_meals);
		i++;
	}
	sem_post(g_death);
	return (NULL);
}
