/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:12:03 by ahuge             #+#    #+#             */
/*   Updated: 2023/11/06 18:18:35 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	x;
	size_t	y;
	size_t	i;
	size_t	j;

	if (dest == 0 && size == 0)
		return (0);
	x = ft_strlen(src);
	y = ft_strlen(dest);
	i = 0;
	j = y;
	if (y < size - 1 && size > 0)
	{
		while (y + i < size - 1 && src[i])
		{
			dest[j] = src[i];
			j++;
			i++;
		}
		dest[j] = 0;
	}
	if (y >= size)
		y = size;
	return (x + y);
}
