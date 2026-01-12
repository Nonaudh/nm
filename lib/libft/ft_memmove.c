/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:02:39 by ahuge             #+#    #+#             */
/*   Updated: 2023/11/09 16:57:47 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	reverse_set_tab(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = n - 1;
	while (i + 1 > 0)
	{
		dest[i] = src[i];
		i--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	char			*ddest;
	const char		*ssrc;

	i = 0;
	ddest = dest;
	ssrc = src;
	if (ssrc == ddest)
		return (ddest);
	if (ssrc < ddest)
	{
		reverse_set_tab(ddest, ssrc, n);
	}
	else
	{
		while (i < n)
		{
			ddest[i] = ssrc[i];
			i++;
		}
	}
	return (ddest);
}
