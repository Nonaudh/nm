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

#include "ft_dprintf.h"

int	ft_dprint_character(int fd, int c)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_dprint_string(int fd, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_dprint_string(fd, "(null)"));
	while (str[i])
		i++;
	write (fd, str, i);
	return (i);
}
