/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-nguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 10:00:45 by thi-nguy          #+#    #+#             */
/*   Updated: 2021/08/10 10:08:24 by thi-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

enum {
	EAT = 1,
	SLEEP = 2,
	THINK = 3,
	TAKE_A_FORK = 4,
	DEAD = 5,
	RIGHT = 6,
	LEFT = 7
};

typedef struct s_arg
{
	int	num_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_meals;
}	t_arg;

typedef struct s_philo {
	int				index;
	int				current_meal;
	int				is_hungry;
	int 			is_dead;
	size_t			t_last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*message;
	pthread_t		thread;
}	t_philo;

typedef struct s_info
{
	t_arg	arg;
	pthread_mutex_t *fork;
	pthread_mutex_t	*message;
	t_philo	*philo;
	int	is_dead;
	size_t t_start;
	int		error;
	int		satisfied_philos;

}	t_info;

long int	ft_atoi(const char *str);
int			ft_isdigit(char c);
int			ft_strlen(const char *str);
char		*ft_strdup(const char *src);

int			check_arg(int ac, char **av);
int			check_isdigit(int ac, char **av);
int			check_int(int ac, char **av);

void		parse_info(int ac, char **av, t_info *info);
void		init_info(t_info *info);
void	init_fork(t_info *info);
void	init_philo(t_info *info);
void	init_one_philo(t_info *info, int index);
int			find_left_fork(int num_philo, int i);
size_t	get_time(void);


//int			init_global_var(void);
//void		init_fork(void);

//void		execute_thread(void);

//void		*routine(void *arg);
//void		get_both_forks(t_philo *one_philo);
//void		get_one_fork(t_philo *one_philo, int which_fork);
//int			assign_first_fork(t_philo *one_philo);

//const char	*get_action_name(int action);
//void		create_message(size_t time, t_philo *one_philo, int action);
//void		print_message(size_t time, t_philo *one_philo, int action);

//size_t		get_time(void);
//void		count_time(size_t time, size_t desired_time);

//void		philo_eat(size_t time_at_beginning_of_eating, t_philo *one_philo);
//void		philo_sleep(size_t g_t_begin_of_sleeping,
//				t_philo *one_philo);

//int			stop_simulation(void);
//void		wait_threads(void);
//void		free_memory(void);

#endif