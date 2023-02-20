/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-bou <abel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 22:06:53 by abel-bou          #+#    #+#             */
/*   Updated: 2022/05/21 15:43:05 by abel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static int	tab(char const *s, char c)
{
	int	i;
	int	num_tab;

	i = 0;
	num_tab = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			num_tab++;
		while (s[i] != c && s[i])
			i++;
	}
	return (num_tab);
}

static char	**ft_allocation(char const *s, char c)
{
	char	**alloc_tab;
	int		i;
	int		j;
	int		k;
	int		start;

	k = tab(s, c);
	alloc_tab = malloc(sizeof(char *) * (k + 1));
	if (!alloc_tab)
		return (NULL);
	i = 0;
	j = 0;
	while (j < k)
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		alloc_tab[j] = ft_substr(s, start, (i - start));
		j++;
	}
	alloc_tab[j] = NULL;
	return (alloc_tab);
}

char	**ft_split(char const *s, char c)
{
	char	**alloc_tab;

	if (!s)
		return (0);
	alloc_tab = ft_allocation(s, c);
	return (alloc_tab);
}
