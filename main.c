/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:41:44 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/05 14:36:36 by aben-ham         ###   ########.fr       */
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

void	show(t_queue *commands)
{
	t_command	*c;
	char		**args;
	t_redt		**redt;

	while (1)
	{
		c = q_dequeue(commands);
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
	}
}

int	main(int ac, char **av, char **env)
{
	char		*str;
	int			status;
	t_queue		*cmds;

	{
		str = readline(PROMT_STR);
		if (str)
		{
			//process_command(str, env);
			cmds = parse_command(str);
			if (cmds)
				show(cmds);
			//waitpid(0, &status, WUNTRACED | WCONTINUED);
			add_history(str);
			free(str);
			free_all();
			//system("leaks minishell");
		}
		else
			exit(0);
	}
	return (0);
}
