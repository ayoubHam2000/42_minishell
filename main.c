/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:41:44 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/24 16:03:36 by aben-ham         ###   ########.fr       */
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
		execute(cmds);
		close_files(cmds);
		free_all();
	}
	add_history(str);
}

void	change_termios(int type)
{
	static struct termios	new_term;
	int						rc;

	if (type == 1)
	{
		rc = tcsetattr(0, 0, &new_term);
		if (rc)
			ft_error_exit("tcsetattr");
	}
	else
	{
		rc = tcgetattr(0, &new_term);
		if (rc)
			ft_error_exit("tcsetattr");
		new_term.c_lflag &= ~(ECHOCTL);
		new_term.c_cc[VMIN] = 0;
		new_term.c_cc[VTIME] = 0;
		rc = tcsetattr(0, 0, &new_term);
		if (rc)
			ft_error_exit("tcsetattr");
	}
}

int	main(int ac, char **av, char **env)
{
	char	*str;

	ac = 0;
	av = NULL;
	env_var(get_copy_env(env));
	init_sigaction();
	change_termios(0);
	while (1)
	{
		str = readline(PROMT_STR);
		if (str)
		{
			du_working(1);
			process_str(str);
			du_working(1);
			change_termios(1);
		}
		else
		{
			printf("exit\n");
			exit(0);
		}
	}
	return (0);
}
