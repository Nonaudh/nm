/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:05:24 by ahuge             #+#    #+#             */
/*   Updated: 2023/11/09 16:08:38 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*tab;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) <= (int)start)
		len = 0;
	else
	{
		if (len > (size_t)ft_strlen(s + start))
			len = (size_t)ft_strlen(s + start);
	}
	tab = malloc(sizeof(char) * (len + 1));
	if (tab == NULL)
		return (NULL);
	while (i < len)
	{
		tab[i] = s[start + i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
