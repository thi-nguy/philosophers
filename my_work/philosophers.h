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
	DEATH = 5,
	RIGHT = 6,
	LEFT = 7,
};


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
    int             order;
    size_t          time_at_end_of_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*message;
}   t_philo;

argument_t      g_info;
t_philo			*g_philo;
pthread_mutex_t	*g_fork;
pthread_mutex_t *g_message;
pthread_t		*g_thread;
size_t			g_start;
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

void	execute_thread(void);

void	*routine(void *arg);
void    get_one_fork(t_philo *one_philo, int which_fork);
size_t			get_time(void);
const char	*get_action_name(int action);
void    create_message(size_t time, t_philo *one_philo, int action);
void    print_message(size_t time, t_philo *one_philo, int action);
int     assign_first_fork(t_philo *one_philo);
void    get_both_forks(t_philo *one_philo);

int 	ft_strlen(const char *str);
char	*ft_strdup(const char *src);

void    philo_eat(size_t time_when_eat, t_philo *one_philo);
void		count_time(size_t time, size_t desired_time);
void philo_sleep(size_t time_when_sleep, t_philo *one_philo);





#endif
