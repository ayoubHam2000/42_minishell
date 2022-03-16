/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:08:12 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/15 22:00:51 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_substr(char const *s1, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*new;

	j = 0;
	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	if (len > i)
		new = (char *)ft_malloc(i + 1);
	else
		new = (char *)ft_malloc(len + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		if (i >= start && j < len)
		{
		new[j++] = s1[i];
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}
