#include "philosophers.h"

int main(int ac, char **av)
{
    argument_t info;
    if (check_arg(ac, av) == -1)
        return (0);
    parse_info(ac, av, &info);



}

void    parse_info(int ac, char **av, argument_t *info)
{
    int num;

    info->num_philo = ft_atoi(av[1]);
    info->time_to_die = ft_atoi(av[2]);
    info->time_to_eat = ft_atoi(av[3]);
    info->time_to_sleep = ft_atoi(av[4]);
    if (ac == 6)
        info->num_must_eat = ft_atoi(av[5]);
}

int     check_arg(int ac, char **av)
{
    if (ac < 5 || ac > 6)
    {
        printf("Number of arguments is not correct.\n");
        return (-1);
    }
	if (check_isdigit(ac, av) == -1)
		return (-1);
	if (check_int(ac, av) == -1)
		return (-1);
	return (1);
}

int	check_isdigit(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if (av[i][j] == '-')
        {
            printf("Arguments should be positive.\n");
            return (-1);
        }
		while (av[i][j] != '\0')
		{
			if (ft_isdigit(av[i][j]) == 1)
				j++;
			else
				return (-1);
		}
		i++;
	}
	return (1);
}

int	check_int(int ac, char **av)
{
	int			i;
	long int	num;

	i = 1;
	while (i < ac)
	{
		num = ft_atoi(av[i]);
		if (num < -2147483648 || num > 2147483647)
        {
            printf("Argument is too large.\n");
			return (-1);
        }
		i++;
	}
	return (1);
}
