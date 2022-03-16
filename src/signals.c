/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:35:07 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/15 23:50:10 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_readline(int s)
{
	
}

static void	sig_handller(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	init_sigaction(void)
{
	if (signal(SIGINT, sig_handller) != 0)
		return (0);
	if (signal(SIGQUIT, SIG_IGN) != 0)
		return (0);
	return (1);
}
