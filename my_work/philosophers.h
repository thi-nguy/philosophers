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
    int num_must_eat;
} argument_t;

int check_isdigit(int ac, char **av);
int check_int(int ac, char **av);
int check_arg(int ac, char **av);
int ft_isdigit(char c);
long int ft_atoi(const char **str);
void    parse_info(int ac, char **av, argument_t *info);




#endif
