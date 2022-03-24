/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:14:12 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/24 11:10:22 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	toupper(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

static int	tolower(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if (tolower(c) || toupper(c))
		return (1);
	return (0);
}
