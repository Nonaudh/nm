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

#include "ft_dprintf.h"

int	ft_dprint_pointer(int fd, unsigned long n)
{
	if (!n)
		return (ft_dprint_string(fd, "(nil)"));
	write(fd, "0x", 2);
	return (ft_dprint_pointer_hexadecimal(fd, n));
}

int	ft_dprint_pointer_hexadecimal(int fd, unsigned long n)
{
	int	nb_lenght;

	nb_lenght = ft_dhexadecimal_lenght(n) + 2;
	if (n >= 16)
	{
		ft_dprint_pointer_hexadecimal(fd, n / 16);
		n = n % 16;
	}
	if (n < 10)
		ft_dprint_character(fd, n + 48);
	if (n > 9)
		ft_dprint_character(fd, n + 87);
	return (nb_lenght);
}

int	ft_dprint_hexadecimal(int fd, unsigned int n, char format)
{
	int	nb_lenght;

	nb_lenght = ft_dhexadecimal_lenght(n);
	if (n >= 16)
	{
		ft_dprint_hexadecimal(fd, n / 16, format);
		n = n % 16;
	}
	if (n < 10)
		ft_dprint_character(fd, n + 48);
	if (n > 9)
	{
		if (format == 'x')
			ft_dprint_character(fd, n + 87);
		if (format == 'X')
			ft_dprint_character(fd, n + 55);
	}
	return (nb_lenght);
}

int	ft_dhexadecimal_lenght(unsigned long n)
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
