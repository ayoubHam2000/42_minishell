/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:41:44 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/09 13:25:34 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

/*
void	process_command(char *str, char **env)
{
	if (!ft_strncmp(str, "exit", ft_strlen("exit")))
		exit(0);
	else
		parse_command(str);
}
*/

void	show(t_command	**commands)
{
	t_command	*c;
	char		**args;
	t_redt		**redt;

	while (1)
	{
		c = *commands;
		if (!c)
			return ;
		args = c->args;
		printf("%s\n", c->command);
		printf("[");
		while (*args)
		{
			printf("%s, ", *args);
			args++;
		}
		printf("]\n");
		redt = c->redt;
		printf("[");
		while (*redt)
		{
			printf("(%s, %d), ", (*redt)->file, (*redt)->r_type);
			redt++;
		}
		printf("]\n");
		commands++;
	}
}

int	get_len_cmmands(t_command **c)
{
	int	n;

	n = 0;
	while (c[n])
		n++;
	return (n);
}

int	main(int ac, char **av, char **env)
{
	char			*str;
	int				status;
	t_command		**cmds;
	int				n;

	while(1){
		str = readline(PROMT_STR);
		//str = "ls";
		if (str)
		{
			if (strlen(str) == 0)
				continue ;
			//process_command(str, env);
			cmds = parse_command(str);
			if (cmds)
			{
				show(cmds);
				//waitpid(0, &status, WUNTRACED | WCONTINUED);
				//free(str);
				//free_all();
				//system("leaks minishell");
				n = get_len_cmmands(cmds);
				int	i = fork();
				if (i == 0)
				{
					fork_pipes(n, cmds, env);
					exit(0);
				}
				waitpid(0, NULL, WUNTRACED | WCONTINUED);
			}
			add_history(str);
		}
		else
			exit(0);
	}
	return (0);
}
