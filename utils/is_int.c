/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:57:47 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/02 16:05:35 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

#define M 9223372036854775808U

static int	is_blank(char c)
{
	if (c == ' ' || c == '\f'
		|| c == '\v' || c == '\t' || c == '\n' || c == '\r')
		return (1);
	return (0);
}

int	is_int(const char *str)
{
	int					signe;
	unsigned long long	res;

	while (is_blank(*str))
		str++;
	signe = 1;
	if (*str == '-')
		signe = -1;
	if (*str == '+' || *str == '-')
		str++;
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10;
		res = res + (*str - '0');
		str++;
		if ((res > M && signe == -1) || (res > M - 1 && signe == 1))
		{
			if (signe < 0)
				return (0);
			if (signe > 0)
				return (0);
		}
	}
	return (1);
}
