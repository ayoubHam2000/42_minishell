/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:41:44 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/04 18:22:10 by aben-ham         ###   ########.fr       */
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
			free(*args);
			args++;
		}
		printf("]\n");
		redt = c->redt;
		printf("[");
		while (*redt)
		{
			printf("(%s, %d), ", (*redt)->file, (*redt)->r_type);
			free((*redt)->file);
			free(*redt);
			redt++;
		}
		free(c->args);
		free(c->redt);
		free(c->command);
		free(c);
		printf("]\n");
	}
}

int	main(int ac, char **av, char **env)
{
	char		*str;
	int			status;
	t_queue		*cmds;

	//process_command(str, env);
	//process_command(av[1], env);
	//printf("%s\n", str);

	//str = "ls $TERM >$t0 | 'ls > |$r $r -la' \"hi >$hi \"";
	//str = "$dgsh > $TERM << $USER \"hi $t\"";
	//str = av[1];
	//cmds = parse_command(str);
	//if (cmds)
	//	show(cmds);
	//system("leaks minishell");
	//if (!init_sigaction())
	//	ft_error_exit(ERR_INTERNAL);
	while (1)
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
		}
		else
			exit(0);
	}
	return (0);
}
