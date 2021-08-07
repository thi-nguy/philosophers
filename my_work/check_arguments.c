#include "philosophers.h"

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
		while (av[i][j] == '+')
			j++;
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
			{
				printf("Arguments should be numbers.\n");
				return (-1);
			}
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
            printf("Argument is out of scope.\n");
			return (-1);
        }
		i++;
	}
	return (1);
}

