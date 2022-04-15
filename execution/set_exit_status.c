/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 21:12:59 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/14 17:40:17 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	du_exit_status(int exit_status, int force)
{
	static int	status;

	if (force)
		status = exit_status;
	else if (exit_status == -1)
		return (status);
	else if (WIFSIGNALED(exit_status))
		status = 128 + WTERMSIG(exit_status);
	else if (WIFEXITED(exit_status))
		status = WEXITSTATUS(exit_status);
	return (status);
}

void	set_exit_status(int exit_status)
{
	du_exit_status(exit_status, 0);
}

int	get_exit_status(void)
{
	return (du_exit_status(-1, 0));
}
