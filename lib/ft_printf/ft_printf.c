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

#include "ft_printf.h"

int	set_format(va_list args, char format)
{
	if (format == 'c')
		return (ft_print_character(va_arg(args, int)));
	if (format == 's')
		return (ft_print_string(va_arg(args, char *)));
	if (format == 'p')
		return (ft_print_pointer(va_arg(args, unsigned long)));
	if (format == 'd' || format == 'i')
		return (ft_print_integer(va_arg(args, int)));
	if (format == 'u')
		return (ft_print_unsigned_decimal(va_arg(args, int)));
	if (format == 'X')
		return (ft_print_hexadecimal(va_arg(args, int), format));
	if (format == 'x')
		return (ft_print_hexadecimal(va_arg(args, int), format));
	if (format == '%')
		return (ft_print_character('%'));
	return (ft_printf("%%%c", format));
}

int	ft_printf(const char *str, ...)
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
			printed_characters += set_format(args, str[i]);
		}
		else
			printed_characters += ft_print_character(str[i]);
		if (str[i])
			i++;
	}
	va_end(args);
	return (printed_characters);
}
