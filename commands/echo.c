/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:22:09 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/03 05:13:58 by yhakkach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>


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