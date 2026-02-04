/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:06:43 by ahuge             #+#    #+#             */
/*   Updated: 2023/12/13 11:06:45 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	set_dformat(int fd, va_list args, char format)
{
	if (format == 'c')
		return (ft_dprint_character(fd, va_arg(args, int)));
	if (format == 's')
		return (ft_dprint_string(fd, va_arg(args, char *)));
	if (format == 'p')
		return (ft_dprint_pointer(fd, va_arg(args, unsigned long)));
	if (format == 'd' || format == 'i')
		return (ft_dprint_integer(fd, va_arg(args, int)));
	if (format == 'u')
		return (ft_dprint_unsigned_decimal(fd, va_arg(args, int)));
	if (format == 'X')
		return (ft_dprint_hexadecimal(fd, va_arg(args, int), format));
	if (format == 'x')
		return (ft_dprint_hexadecimal(fd, va_arg(args, int), format));
	if (format == '%')
		return (ft_dprint_character(fd, '%'));
	return (ft_dprintf(fd, "%%%c", format));
}

int	ft_dprintf(int fd, const char *str, ...)
{
	int		i;
	va_list	args;
	int		printed_characters;

	i = 0;
	printed_characters = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			printed_characters += set_dformat(fd, args, str[i]);
		}
		else
			printed_characters += ft_dprint_character(fd, str[i]);
		if (str[i])
			i++;
	}
	va_end(args);
	return (printed_characters);
}
