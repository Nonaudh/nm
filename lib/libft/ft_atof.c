/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:07:57 by ahuge             #+#    #+#             */
/*   Updated: 2024/03/05 15:22:30 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_space_and_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	while (str[*i] == ' ' || (str[*i] > 8 && str[*i] < 14))
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -sign;
		(*i)++;
	}
	return (sign);
}

double	ft_atof(const char *str)
{
	int			i;
	double		div;
	double		nb;
	int			sign;

	i = 0;
	div = 0.1;
	sign = 1;
	nb = 0;
	sign = skip_space_and_sign(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10.0) + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb + (str[i] - '0') * div;
		div /= 10;
		i++;
	}
	return (nb * sign);
}
