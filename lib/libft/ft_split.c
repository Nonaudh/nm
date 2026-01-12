/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:12:08 by ahuge             #+#    #+#             */
/*   Updated: 2023/11/09 16:43:30 by ahuge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			x++;
		i++;
	}
	return (x);
}

static int	free_the_tab(char **tab, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

static void	ft_tabset(char **tab, const char *s, int c)
{
	int	i;
	int	x;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		x = 0;
		while (s[i + x] && s[i + x] != c)
			x++;
		if (x > 0)
		{
			tab[j] = ft_substr(s, i, x);
			if (tab[j] == 0)
				if (!free_the_tab(tab, j))
					return ;
			j++;
			i = i + x;
		}
		else
			i++;
	}
	tab[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	int		x;
	char	**tab;

	if (!s)
		return (NULL);
	x = count_word(s, c);
	tab = malloc(sizeof(char *) * (x + 1));
	if (tab == 0)
		return (NULL);
	ft_tabset(tab, s, c);
	return (tab);
}
