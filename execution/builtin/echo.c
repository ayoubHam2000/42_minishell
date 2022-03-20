/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:22:09 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/20 20:19:30 by yhakkach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




int		ft_strevery(char *str , char target)
{

	while (*str)
	{
		if (*str != target)
			return 0;
		++str;
	}
	return 1;
	
}

int	ft_echo(char **cmd)
{
	int	i;
	int	control;

	i = 0;
	control = 0;
	
	if (ft_arrlen((void **)cmd) == 0)
	{
		printf("\n");
		return 0;
	}
	while (cmd[i] && !ft_strncmp(cmd[i], "-n",  2))
	{
		if (!ft_strevery(cmd[i] +1, 'n'))
		{
			break;	
		}
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
	return (0);
}
