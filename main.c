/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:41:44 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/10 18:47:28 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

int	main(int ac, char **av, char **env)
{
	char			*str;
	int				status;
	t_command		**cmds;

	while(1){
		str = readline(PROMT_STR);
		if (str)
		{
			if (strlen(str) == 0)
				continue ;
			cmds = parse_command(str);
			if (cmds)
			{
				show(cmds);
				execute(cmds, env);
				wait(NULL);
				free_all();
			}
			add_history(str);
		}
		else
			exit(0);
	}
	return (0);
}
