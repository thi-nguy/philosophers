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
    PUT_DOWN_LEFT_FORK = 5,
    PUT_DOWN_RIGHT_FORK = 6,
	DEAD = 7,
	RIGHT = 8,
	LEFT = 9
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
    int             order;
	int				current_meal;
	int				is_hungry;
    size_t          time_at_end_of_meal;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*message;
}   t_philo;

argument_t      g_info;
t_philo			*g_philo;
pthread_mutex_t	*g_fork;
pthread_t		*g_thread;
pthread_mutex_t *g_message;
size_t			g_time_at_beginning;
int				g_satisfied_philos;
int				g_dead_philo;

int ft_isdigit(char c);
int 	ft_strlen(const char *str);
char	*ft_strdup(const char *src);
long int ft_atoi(const char *str);

int check_isdigit(int ac, char **av);
int check_int(int ac, char **av);
int check_arg(int ac, char **av);
void    parse_info(int ac, char **av);

void	init_info_philo(void);
void	init_global_var(void);
int		find_left_fork(int i);
void	init_fork(void);

void	execute_thread(void);

void	*routine(void *arg);
void    get_both_forks(t_philo *one_philo);
void    get_one_fork(t_philo *one_philo, int which_fork);
int     assign_first_fork(t_philo *one_philo);

const char	*get_action_name(int action);
void    create_message(size_t time, t_philo *one_philo, int action);
void    print_message(size_t time, t_philo *one_philo, int action);

size_t			get_time(void);
void		count_time(size_t time, size_t desired_time);

void    philo_eat(size_t time_at_beginning_of_eating, t_philo *one_philo);
void philo_sleep(size_t g_time_at_beginning_of_sleeping, t_philo *one_philo);

int stop_simulation(void);
void		wait_threads(void);
void free_memory(void);

#endif
