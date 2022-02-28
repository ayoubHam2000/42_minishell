/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:41:44 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/28 14:38:23 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

int	parse_command(char *str, char **env);

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
	//char		*str;
	//int			status;

	char	*str = "ls $";
	//process_command(str, env);
	//process_command(av[1], env);
	printf("%s\n", str);
	parse_command(str, env);
	//system("leaks minishell");
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
