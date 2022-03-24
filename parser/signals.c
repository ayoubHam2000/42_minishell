/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:35:07 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/24 11:09:45 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	du_working(int affect)
{
	static int	i;

	if (affect)
		i = !i;
	return (i);
}

static void	sig_handller(int sig)
{
	if (sig == SIGINT)
	{
		if (!du_working(0))
		{
			ft_putstr("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

int	init_sigaction(void)
{
	if (signal(SIGINT, sig_handller) != 0)
		return (0);
	if (signal(SIGQUIT, sig_handller) != 0)
		return (0);
	return (1);
}
