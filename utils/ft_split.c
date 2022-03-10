/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:02:46 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/10 13:51:15 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
* Allocates (with ft_malloc(3)) and returns an array
	of strings obtained by splitting ’s’ using the
	character ’c’ as a delimiter. The array must be
	ended by a NULL pointer.
* return : The array of new strings resulting from the split.
	NULL if the allocation fails.
*/

static size_t	nb_place(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (1)
	{
		if (*s != c)
			count++;
		while (*s != c && *s != 0)
			s++;
		if (*s == 0)
			break ;
		while (*s == c && *s != 0)
			s++;
		if (*s == 0)
			break ;
	}
	return (count);
}

static size_t	part_len(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s != c && *s != 0)
	{
		count++;
		s++;
	}
	return (count);
}

static int	fill_table(char const *s, char c, char **tab)
{
	size_t	count;
	size_t	size_tab;

	size_tab = 0;
	while (1)
	{
		while (*s == c && *s != 0)
			s++;
		if (*s == 0)
			break ;
		count = part_len(s, c);
		*tab = ft_malloc(part_len(s, c) + 1);
		if (!(*tab))
			return (0);
		ft_strlcpy(*tab, s, count + 1);
		s = s + count;
		tab++;
		size_tab++;
	}
	*tab = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	size_t	count;
	char	**tab;

	if (!s)
		return (NULL);
	count = nb_place(s, c);
	tab = ft_malloc(sizeof(char *) * (count + 1));
	if (!tab || !fill_table(s, c, tab))
		return (NULL);
	return (tab);
}
