/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 21:12:59 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/23 21:07:46 by yhakkach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_exit_status(int new_status)
{
	static int	status;
	
	if (new_status >= 0)
		status = new_status;
	return (status);
}

void	set_exit_status(int new_status, int new_sig)
{
	static int	signal;
	char		**status;

	if (new_sig)
	{
		signal = new_sig;
		return ;
	}
	if (signal)
		get_exit_status(128 + signal);
	else
		get_exit_status(new_status);
	signal = 0;
}
