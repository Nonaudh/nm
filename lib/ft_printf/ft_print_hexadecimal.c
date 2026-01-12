/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexadecimal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:08:21 by ahuge             #+#    #+#             */
/*   Updated: 2023/12/13 11:08:24 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_pointer(unsigned long n)
{
	if (!n)
		return (ft_print_string("(nil)"));
	write(1, "0x", 2);
	return (ft_print_pointer_hexadecimal(n));
}

int	ft_print_pointer_hexadecimal(unsigned long n)
{
	int	nb_lenght;

	nb_lenght = ft_hexadecimal_lenght(n) + 2;
	if (n >= 16)
	{
		ft_print_pointer_hexadecimal(n / 16);
		n = n % 16;
	}
	if (n < 10)
		ft_print_character(n + 48);
	if (n > 9)
		ft_print_character(n + 87);
	return (nb_lenght);
}

int	ft_print_hexadecimal(unsigned int n, char format)
{
	int	nb_lenght;

	nb_lenght = ft_hexadecimal_lenght(n);
	if (n >= 16)
	{
		ft_print_hexadecimal(n / 16, format);
		n = n % 16;
	}
	if (n < 10)
		ft_print_character(n + 48);
	if (n > 9)
	{
		if (format == 'x')
			ft_print_character(n + 87);
		if (format == 'X')
			ft_print_character(n + 55);
	}
	return (nb_lenght);
}

int	ft_hexadecimal_lenght(unsigned long n)
{
	int	lenght;

	lenght = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 16;
		lenght++;
	}
	return (lenght);
}
