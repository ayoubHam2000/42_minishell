/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:22:09 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/10 18:58:35 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **args)
{
	int	i;
	int	control;

	i = 2;
	control = 0;
	if (ft_arrlen(args) == 1)
	{
		printf("\n");
		return ;
	}
	if (!strncmp(args[i], "-n", strlen(args[1])))
	{
		control = 1;
		i++;
	}
	while (args[i])
	{
		if (!args[i + 1])
			printf("%s", args[i++]);
		else
			printf("%s ", args[i++]);
	}
	if (!control)
		printf("\n");
}
