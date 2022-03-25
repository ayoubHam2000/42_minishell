/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:41:54 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/25 16:45:00 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_fd_out(int new)
{
	static int	out = 1;

	if (new > 1)
		out = new;
	else if (new == 0)
		out = 1;
	return (out);
}

void	ft_print_out(const char *str)
{
	ft_putstr_fd(get_fd_out(-1), str);
}
