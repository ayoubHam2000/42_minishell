/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:35:07 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/20 21:03:58 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handller(int sig)
{
	g_sig = sig;
	if (sig == SIGINT)
	{
		ft_putstr("\b\b  \n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		//rl_on_new_line();
		//rl_replace_line("", 0);
		//printf("\b\b  \b\b\n");
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
