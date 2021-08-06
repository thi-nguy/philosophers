/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <mkristie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:21:37 by mkristie          #+#    #+#             */
/*   Updated: 2020/12/03 13:31:36 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		error_fatal(void)
{
	ft_putstr_fd("error: fatal", 2);
	exit(FATAL_ERR);
}

void		ft_alloc_check(void *ptr)
{
	if (!ptr)
	{
		ft_putstr_fd("error: out of memory\n", 2);
		exit(MALLOC_ERR);
	}
}
