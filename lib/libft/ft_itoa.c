/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:58:43 by ahuge             #+#    #+#             */
/*   Updated: 2023/11/09 15:20:17 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	n_len(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	if (n == 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*tab;
	long	nb;

	nb = (long)n;
	i = n_len(nb);
	tab = ft_calloc((i + 1), sizeof(char));
	if (tab == NULL)
		return (NULL);
	if (n < 0)
	{
		tab[0] = '-';
		nb = -nb;
	}
	tab[i] = 0;
	i--;
	while (i >= 0 && tab[i] != '-')
	{
		tab[i] = nb % 10 + '0';
		nb = nb / 10;
		i--;
	}
	return (tab);
}
