/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:57:47 by ahuge             #+#    #+#             */
/*   Updated: 2023/11/08 19:04:36 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t l)
{
	size_t	i;
	size_t	y;

	i = 0;
	if (big == 0 && l == 0)
		return (0);
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] != '\0')
	{
		y = 0;
		while (big[i + y] == little[y] && (i + y) < l)
		{
			if (little[y] == '\0')
				return ((char *)big + i);
			y++;
		}
		if (little[y] == '\0')
			return ((char *)big + i);
		i++;
	}
	return (0);
}
