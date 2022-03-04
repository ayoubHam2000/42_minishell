/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:29:10 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/04 20:31:22 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static size_t	nb_place(char const *s, int (*f)(char c))
{
	size_t	count;

	count = 0;
	while (1)
	{
		if (!f(*s))
			count++;
		while (!f(*s) && *s != 0)
			s++;
		if (*s == 0)
			break ;
		while (f(*s) && *s != 0)
			s++;
		if (*s == 0)
			break ;
	}
	return (count);
}

static size_t	part_len(char const *s, int (*f)(char c))
{
	size_t	count;

	count = 0;
	while (!f(*s) && *s != 0)
	{
		count++;
		s++;
	}
	return (count);
}

static void	free_table(char **tab, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		//free(tab[i]);
		i++;
	}
	//free(tab);
}

static int	fill_table(char const *s, int (*f)(char c), char **tab)
{
	size_t	count;
	size_t	size_tab;

	size_tab = 0;
	while (1)
	{
		while (f(*s) && *s != 0)
			s++;
		if (*s == 0)
			break ;
		count = part_len(s + 1, f) + 1;
		*tab = ft_malloc(count + 1);
		if (!(*tab))
		{
			free_table(tab - size_tab, size_tab);
			return (0);
		}
		ft_strlcpy(*tab, s, count + 1);
		s = s + count;
		tab++;
		size_tab++;
	}
	*tab = NULL;
	return (1);
}

char	**ft_fsplit(char const *s, int (*f)(char c))
{
	size_t	count;
	char	**tab;

	if (!s)
		return (NULL);
	f(0);
	count = nb_place(s, f);
	tab = ft_malloc(sizeof(char *) * (count + 1));
	if (!tab || !fill_table(s, f, tab))
		return (NULL);
	return (tab);
}
