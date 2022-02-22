/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:41:44 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/22 18:52:07 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_command(char *str)
{
	if (!ft_strncmp(str, "exit", ft_strlen("exit")))
		exit(0);
}

int	main(int ac, char **av)
{
	char		*str;

	if (!init_sigaction())
		ft_error_exit(ERR_INTERNAL);
	while (1)
	{
		str = readline(PROMT_STR);
		if (str)
		{
			process_command(str);
			add_history(str);
			free(str);
		}
		else
			exit(0);
	}
	return (0);
}
