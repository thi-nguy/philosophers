#include "philosophers.h"

long int	ft_atoi(const char *str)
{
	long int	nb;
	int			i;
	int			s;

	i = 0;
	s = 1;
	nb = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			s = -s;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return ((long int)(s * nb));
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
