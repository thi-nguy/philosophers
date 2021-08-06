/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:27:01 by mkristie          #+#    #+#             */
/*   Updated: 2020/12/04 22:39:20 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_PHILO_TWO_H
# define PHILOSOPHERS_PHILO_TWO_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <stdio.h>

enum {
	EAT,
	SLEEP,
	THINK,
	TAKEN_A_FORK,
	DEATH,
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
	_Bool				is_hungry;
	size_t				last_meal_time;
}						t_philo;

extern	t_philo			*g_philos;
extern	sem_t			*g_forks;
extern	sem_t			*g_message_sem;
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
_Bool					init_forks(int number_of_forks);
void					init_philo(t_input input);
_Bool					init_input(t_input input);
_Bool					parse(int ac, char **av, t_input *input);
size_t					get_time();
char					*get_action(int	action);
char					*create_message(size_t time, int philo, int action);
void					print_message(size_t time, int philo, int action);
void					*eat_sleep_repeat(void *val);
_Bool					free_all_mem(int size);

#endif
