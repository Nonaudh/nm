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

#include "ft_printf.h"

int	ft_print_unsigned_decimal(unsigned int n)
{
	int	nb_lenght;

	nb_lenght = ft_decimal_lenght(n);
	if (n >= 10)
	{
		ft_print_unsigned_decimal(n / 10);
		n = n % 10;
	}
	ft_print_character(n + 48);
	return (nb_lenght);
}

int	ft_print_integer(long n)
{
	int	nb_lenght;

	nb_lenght = ft_decimal_lenght(n);
	if (n < 0)
	{
		ft_print_character('-');
		n = -n;
	}
	if (n >= 10)
	{
		ft_print_integer(n / 10);
		n = n % 10;
	}
	ft_print_character(n + 48);
	return (nb_lenght);
}

int	ft_decimal_lenght(long n)
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
