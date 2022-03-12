/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:50:03 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/12 16:51:00 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	num_len(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (-1 * n);
	return (n);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*res;

	count = num_len(n);
	if (n < 0)
		count++;
	res = ft_malloc(count + 1);
	*(res + count) = 0;
	if (n == 0)
		*res = '0';
	else
	{
		while (n != 0)
		{
			*(res + count - 1) = ft_abs(n % 10) + '0';
			count--;
			n = n / 10;
		}
		if (count == 1)
			*(res) = '-';
	}
	return (res);
}
