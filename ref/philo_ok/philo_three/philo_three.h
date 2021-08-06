/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:27:01 by mkristie          #+#    #+#             */
/*   Updated: 2020/12/03 14:09:20 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_PHILO_THREE_H
# define PHILOSOPHERS_PHILO_THREE_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>

enum {
	EAT,
	SLEEP,
	THINK,
	TAKEN_A_FORK,
	DEATH,
	MALLOC_ERR,
	FATAL_ERR,
	FULL
};

typedef struct			s_philo {
	int					n_philos;
	size_t				num;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				desired_meals;
	size_t				current_meal;
	pid_t				*pid;
	pthread_t			thread;
	_Bool				is_hungry;
	size_t				last_meal_time;
}						t_philo;

extern	t_philo			*g_philo;
extern	sem_t			*g_forks;
extern	sem_t			*g_message_sem;
extern	size_t			g_start_time;

size_t					ft_strlen(const char *s);
void					ft_putstr_fd(char *s, int fd);
char					*ft_itoa(size_t num);
int						ft_atoi(const char *str);
int						ft_isdigit(int c);
char					*ft_strdup(const char *s1);
size_t					ft_strlcat(char *dst, const char *src, size_t dstsize);
void					ft_alloc_check(void *ptr);
void					error_fatal(void);
_Bool					init_semaphors(int size);
_Bool					parse(int ac, char **av);
size_t					get_time();
char					*get_action(int	action);
char					*create_message(size_t time, int philo, int action);
void					print_message(size_t time, int philo, int action);
void					*eat_sleep_repeat();

#endif
