/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:41:44 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/01 18:23:44 by aben-ham         ###   ########.fr       */
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



int	main(int ac, char **av, char **env)
{
	char		*str;
	int			status;
	t_queue		*cmds;

	//process_command(str, env);
	//process_command(av[1], env);
	//printf("%s\n", str);
	str = "ls >a -la | grep 'books \"are great' \"it's like\" > p";
	cmds = parse_command(str);
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
