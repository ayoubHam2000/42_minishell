/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:41:44 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/16 15:47:07 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_str(char *str)
{
	t_command		**cmds;

	if (strlen(str) == 0)
		return ;
	cmds = parse_command(str);
	if (cmds)
	{
		open_files(cmds);
		//show(cmds);
		int i = execute(cmds);
		printf("exit status : %d\n", i);
		close_files(cmds);
		free_all();
	}
	add_history(str);
}

//test
int	main(int ac, char **av, char **env)
{
	char	*str;

	env_var(get_copy_env(env));
	init_sigaction();
	while(1)
	{
		str = readline(PROMT_STR);
		g_sig = 0;
		if (str)
		{
			process_str(str);
		}
		else
		{
			printf("exit\n");
			exit(0);
		}
	}
	return (0);
}
