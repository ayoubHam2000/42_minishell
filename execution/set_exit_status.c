/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_exit_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 21:12:59 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/24 10:50:29 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	du_exit_status(int exit_status)
{
	static int	status;

	if (exit_status == -1)
		return (status);
	else if (WIFSIGNALED(exit_status))
		status = 128 + WTERMSIG(exit_status);
	else if (WIFEXITED(exit_status))
		status = WEXITSTATUS(exit_status);
	return (status);
}

void	set_exit_status(int exit_status)
{
	du_exit_status(exit_status);
}

int	get_exit_status(void)
{
	return (du_exit_status(-1));
}
