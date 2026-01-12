/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_character.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 11:06:11 by ahuge             #+#    #+#             */
/*   Updated: 2023/12/13 11:06:15 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_character(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_string(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_print_string("(null)"));
	while (str[i])
		i++;
	write (1, str, i);
	return (i);
}
