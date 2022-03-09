/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:22:09 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/09 10:03:02 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_arraylen(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
	{
		i++;
	}
	return (i);
}

void	echocmd(char **cmd)
{
	int	i;
	int	control;

	i = 2;
	control = 0;
	if (ft_arraylen(cmd) == 1)
	{
		printf("\n");
		return ;
	}
	if (!strncmp(cmd[i], "-n", strlen(cmd[1])))
	{
		control = 1;
		i++;
	}
	while (cmd[i])
	{
		if (!cmd[i + 1])
			printf("%s", cmd[i++]);
		else
			printf("%s ", cmd[i++]);
	}
	if (!control)
		printf("\n");
}

int     main(int argc,char **argv,char **envp)
{	
		if (!strncmp(argv[1], "echo",strlen("echo")))
	{
		echocmd(argv);
	}
}