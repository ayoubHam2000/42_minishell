/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:22:09 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/12 16:29:18 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **cmd)
{
	int	i;
	int	control;

	i = 0;
	control = 0;
	i = 0;
	if (ft_arrlen(cmd) == 0)
	{
		printf("\n");
		return ;
	}
	while (cmd[i] && !ft_strncmp(cmd[i], "-n", ft_strlen(cmd[i])))
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