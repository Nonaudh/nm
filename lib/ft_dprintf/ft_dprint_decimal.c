/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_decimal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:06:51 by ahuge             #+#    #+#             */
/*   Updated: 2023/12/13 11:06:53 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	ft_dprint_unsigned_decimal(int fd, unsigned int n)
{
	int	nb_lenght;

	nb_lenght = ft_ddecimal_lenght(n);
	if (n >= 10)
	{
		ft_dprint_unsigned_decimal(fd, n / 10);
		n = n % 10;
	}
	ft_dprint_character(fd, n + 48);
	return (nb_lenght);
}

int	ft_dprint_integer(int fd, long n)
{
	int	nb_lenght;

	nb_lenght = ft_ddecimal_lenght(n);
	if (n < 0)
	{
		ft_dprint_character(fd, '-');
		n = -n;
	}
	if (n >= 10)
	{
		ft_dprint_integer(fd, n / 10);
		n = n % 10;
	}
	ft_dprint_character(fd, n + 48);
	return (nb_lenght);
}

int	ft_ddecimal_lenght(long n)
{
	int	nb_lenght;

	nb_lenght = 0;
	if (n <= 0)
	{
		n = -n;
		nb_lenght++;
	}
	while (n > 0)
	{
		n = n / 10;
		nb_lenght++;
	}
	return (nb_lenght);
}
