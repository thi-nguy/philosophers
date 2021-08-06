#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct argument_s
{
    int num_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int meals_must_eat;
} argument_t;

typedef struct			s_philo {
	int				current_meal;
	int				is_hungry;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*message_mutex;
}   t_philo;

argument_t      g_info;
t_philo			*g_philo;
pthread_mutex_t	*g_fork;
pthread_t		*g_thread;
// size_t			g_start_time;
// int				g_full_philos;
// int				g_error;

int check_isdigit(int ac, char **av);
int check_int(int ac, char **av);
int check_arg(int ac, char **av);
int ft_isdigit(char c);
long int ft_atoi(const char *str);
void    parse_info(int ac, char **av);

void	init_info_philo(void);
int		find_right_fork(int i);
void	init_fork(void);







#endif
