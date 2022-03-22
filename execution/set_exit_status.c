/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 21:12:59 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/22 21:41:46 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit_status(int new_status, int new_sig)
{
	static int	signal;

	if (new_sig)
	{
		signal = new_sig;
		return ;
	}
	if (signal)
		printf("exit status :%d %d\n", 128 + signal, new_status);
	else
		printf("exit status : %d\n", new_status);
	signal = 0;
}
