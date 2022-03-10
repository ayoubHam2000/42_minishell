/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:16:22 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/10 14:42:20 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static size_t	min(size_t a, size_t b)
{
	if (a > b)
		return (b);
	return (a);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	substr_len;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start || len == 0)
	{
		res = ft_malloc(1);
		if (!res)
			return (NULL);
		*res = 0;
	}
	else
	{
		substr_len = min(ft_strlen(s) - start, len);
		res = ft_malloc(substr_len + 1);
		if (!res)
			return (NULL);
		ft_strlcpy(res, s + start, substr_len + 1);
	}
	return (res);
}
