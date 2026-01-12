/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:23:23 by ahuge             #+#    #+#             */
/*   Updated: 2023/11/09 16:08:08 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*tab;
	long		nm_size;

	nm_size = nmemb * size;
	if (nm_size < 0 || ((long)nmemb < 0 && (long)size))
		return (NULL);
	tab = malloc(nm_size);
	if (!tab)
		return (NULL);
	ft_bzero(tab, nm_size);
	return (tab);
}
