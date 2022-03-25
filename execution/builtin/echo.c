/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:22:09 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/25 16:47:07 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strevery(char *str, char target)
{
	while (*str)
	{
		if (*str != target)
			return (0);
		++str;
	}
	return (1);
}

void	print_cmd(int i, char **cmd)
{
	while (cmd[i])
	{
		if (!cmd[i + 1])
			ft_print_out(cmd[i++]);
		else
			ft_print_out(cmd[i++]);
	}
}

int	ft_echo(char **cmd)
{
	int	i;
	int	control;

	i = 0;
	control = 0;
	if (ft_arrlen((void **)cmd) == 0)
	{
		ft_print_out("\n");
		return (0);
	}
	while (cmd[i] && !ft_strncmp(cmd[i], "-n", 2))
	{
		if (!ft_strevery(cmd[i] +1, 'n'))
			break ;
		control = 1;
		i++;
	}
	print_cmd(i, cmd);
	if (!control)
		ft_print_out("\n");
	return (0);
}
