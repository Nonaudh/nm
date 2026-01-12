/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:39:12 by ahuge             #+#    #+#             */
/*   Updated: 2023/11/22 18:00:16 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	int		x;

	i = 0;
	x = ft_strlen_gnl(src);
	if (!dest || !src)
		return (0);
	if (size != 0)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = 0;
	}
	return (x);
}

char	*ft_strchr_gnl(const char *src, int c)
{
	int	i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i] && src[i] != (char) c)
		i++;
	if (src[i] == (char) c)
		return ((char *)src + i);
	return (NULL);
}

char	*ft_strjoin_gnl(char *line, char *buffer)
{
	int		i;
	int		z;
	char	*tab;

	i = 0;
	z = 0;
	if (!line || !buffer)
		return (NULL);
	tab = malloc(sizeof(char) * (ft_strlen_gnl(line)
				+ ft_strlen_gnl(buffer) + 1));
	if (tab == NULL)
		return (NULL);
	while (line[i])
	{
		tab[i] = line[i];
		i++;
	}
	while (buffer[z])
	{
		tab[i + z] = buffer[z];
		z++;
	}
	tab[i + z] = 0;
	free (line);
	return (tab);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		i++;
	}
	return (i);
}
