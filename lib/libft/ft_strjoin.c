/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:39:12 by ahuge             #+#    #+#             */
/*   Updated: 2023/11/07 15:56:32 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		x;
	int		i;
	int		z;
	char	*tab;

	i = 0;
	z = 0;
	if (!s1 && !s2)
		return (NULL);
	x = ft_strlen(s1) + ft_strlen(s2);
	tab = malloc(sizeof(char) * (x + 1));
	if (tab == NULL)
		return (NULL);
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	while (s2[z])
	{
		tab[i + z] = s2[z];
		z++;
	}
	tab[i + z] = 0;
	return (tab);
}
