/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:41:44 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/02 16:30:45 by aben-ham         ###   ########.fr       */
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

void	show(t_queue *q)
{
	t_node	*node;
	t_node	*tmp;

	node = q->first;
	while (node)
	{
		printf("Command : %s\n", (char *)(p_cmd(node)->command));
		printf("Args : [");
		tmp = p_cmd(node)->q_args->first;
		while (tmp)
		{
			printf("%s, ", (char *)(tmp->p));
			tmp = tmp->next;
		}
		printf("]\n");
		printf("Redt : [");
		tmp = p_cmd(node)->q_redt->first;
		while (tmp)
		{
			printf("(%d - %s), ", p_redt(tmp)->r_type, p_redt(tmp)->file);
			tmp = tmp->next;
		}
		printf("]\n");
		node = node->next;
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
	str = "ls -la > a < b";
	cmds = parse_command(str);
	show(cmds);
	/*if (!init_sigaction())
		ft_error_exit(ERR_INTERNAL);
	while (1)
	{
		str = readline(PROMT_STR);
		if (str)
		{
			process_command(str, env);
			waitpid(0, &status, WUNTRACED | WCONTINUED);
			add_history(str);
			free(str);
		}
		else
			exit(0);
	}*/
	return (0);
}
//0x00006030000003a0