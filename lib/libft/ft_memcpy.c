/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:33:08 by ahuge             #+#    #+#             */
/*   Updated: 2023/11/06 16:46:38 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*sdest;
	const unsigned char	*ssrc;
	size_t				i;

	i = 0;
	sdest = dest;
	ssrc = src;
	if (dest == 0 && src == 0)
		return (0);
	while (i < n)
	{
		*(sdest + i) = *(ssrc + i);
		i++;
	}
	return (dest);
}
