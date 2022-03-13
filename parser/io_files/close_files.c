/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 21:27:10 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/13 10:42:05 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_files(t_command **cmds)
{
	int	c;

	c = 0;
	while (cmds[c])
	{
		if (cmds[c]->fd[0] > 1)
			close(cmds[c]->fd[0]);
		if (cmds[c]->fd[1] > 1)
			close(cmds[c]->fd[1]);
		c++;
	}
}
