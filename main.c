/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:41:44 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/22 16:44:44 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_command(char *str)
{
	if (!ft_strncmp(str, "exit", ft_strlen("exit")))
		exit(0);
}

void	sig_handller(int sig)
{
	//rl_on_new_line();
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	//ft_putstr("\nminishell$ ");
	//ft_putstr("=");
}

int	init_sigaction(void)
{
	int			i;
	sigset_t	set;
	t_sigaction	s;

	i = -1;
	while (++i < sizeof(t_sigaction))
		*((char *)(&s) + i) = 0;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	s.sa_mask = set;
	s.__sigaction_u.__sa_handler = sig_handller;
	if (sigaction(SIGINT, &s, NULL) != 0)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	char		*str;

	if (!init_sigaction())
		ft_error_exit("Internal Error\n");
	while (1)
	{
		str = readline("minishell$ ");
		if (str)
		{
			//ft_putstr("-");
			process_command(str);
			add_history(str);
			free(str);
		}
		//else
		//	ft_error("Error : Not Enough memory\n");


		
	}
	return (0);
}
