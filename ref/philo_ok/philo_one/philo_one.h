/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:27:01 by mkristie          #+#    #+#             */
/*   Updated: 2020/12/04 20:50:52 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_PHILO_ONE_H
# define PHILOSOPHERS_PHILO_ONE_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <stdio.h>

enum {
	EAT,
	SLEEP,
	THINK,
	TAKEN_A_FORK,
	DEATH,
	RIGHT,
	LEFT,
	FATAL_ERR
};

typedef struct			s_input {
	int					n_philos;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				desired_meals;
}						t_input;

typedef struct			s_philo {
	size_t				num;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				desired_meals;
	size_t				current_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*message_mutex;
	_Bool				is_hungry;
	size_t				last_meal_time;
}						t_philo;

extern	t_philo			*g_philos;
extern	pthread_mutex_t	*g_forks;
extern	pthread_t		*g_philo_threads;
extern	size_t			g_start_time;
extern	int				g_full_philos;
extern	int				g_error;

size_t					ft_strlen(const char *s);
void					ft_putstr_fd(char *s, int fd);
char					*ft_itoa(size_t num);
int						ft_atoi(const char *str);
int						ft_isdigit(int c);
char					*ft_strdup(const char *s1);
size_t					ft_strlcat(char *dst, const char *src, size_t dstsize);
void					ft_alloc_check(void *ptr);
void					init_forks(int number_of_forks);
void					init_philo(t_input input);
_Bool					init_input(t_input input);
_Bool					parse(int ac, char **av, t_input *input);
size_t					get_time();
char					*get_action(int	action);
void					print_message(size_t time, int philo, int action, \
											pthread_mutex_t *message_mutex);
void					get_forks(t_philo *philo);
void					*eat_sleep_repeat(void *val);
_Bool					free_all_mem(int size);

#endif
