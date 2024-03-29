/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thi-nguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 10:00:45 by thi-nguy          #+#    #+#             */
/*   Updated: 2021/08/13 22:52:32 by thi-nguy         ###   ########.fr       */
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

typedef enum e_state {
	EAT,
	SLEEP,
	THINK,
	FORK,
	ALIVE,
	DEAD,
	STOP,
	TAKE_RIGHT_FORK,
	TAKE_LEFT_FORK,
}	t_state;

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
	size_t			t_last_meal;
	pthread_t		thread;
	t_state			state;
	int				*satisfied_philo;
	t_state 		*global_state;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*message;
	t_arg			*arg;
	size_t			*t_start;
}	t_philo;

typedef struct s_info
{
	t_arg			arg;
	t_philo			*philo;
	pthread_mutex_t *fork;
	pthread_mutex_t	*message;
	t_state			global_state;
	size_t 			t_start;
	pthread_t		global_thread;
	int				satisfied_philos;

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
void		init_fork(t_info *info);
void		init_philo(t_info *info);
void		init_one_philo(t_info *info, int index);
int			find_right_fork(int num_philo, int i);
int			assign_state(int index);

size_t		get_time(void);
void		free_memory(t_info *info);

void		execute_thread(t_info *info);
void		*routine(void *arg);



const char	*get_action_name(int action);
void		create_message(t_philo *one_philo, int action);
void		print_message(t_philo *one_philo, int action);
void		count_time(size_t time, size_t desired_time);

void		end_simulation(t_info *info);

void		take_forks(t_philo *one_philo);
void		do_eat(t_philo *one_philo);
void		do_sleep(t_philo *one_philo);
void		do_think(t_philo *one_philo);
void	 	die(t_philo *one_philo, size_t time_at_dying);

int			assign_fork(int index);
void		*check_status(void *arg);

#endif
