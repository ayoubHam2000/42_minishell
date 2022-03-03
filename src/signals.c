/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:35:07 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/03 08:50:06 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_handller(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr(PROMT_STR"   \n");
		//rl_on_new_line();
		//rl_replace_line("", 0);
		//rl_redisplay();
	}
}

int	init_sigaction(void)
{
	/*int			i;
	sigset_t	set;
	t_sigaction	s;

	i = -1;
	while (++i < sizeof(t_sigaction))
		*((char *)(&s) + i) = 0;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	s.sa_mask = set;
	s.__sigaction_u.__sa_handler = sig_handller;
	//if (sigaction(SIGINT, &s, NULL) != 0)
	//	return (0);
	if (signal(SIGQUIT, SIG_IGN) != 0)
		return (0);*/
	return (1);
}
