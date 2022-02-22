/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:49:40 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/22 10:19:59 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	i;

	if (n == 0)
		return (NULL);
	i = c;
	while (n > 1 && *((unsigned char *)s) != i)
	{
		s++;
		n--;
	}
	if (n == 1 && *((unsigned char *)s) != i)
		return (NULL);
	return ((void *)s);
}
