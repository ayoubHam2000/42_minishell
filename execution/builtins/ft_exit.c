/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:08:50 by hbourkan          #+#    #+#             */
/*   Updated: 2022/04/15 18:19:13 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	code_is_number(char **args, int fd)
{
	if (counter(args) > 1 && is_number(args[0]))
	{
		ft_putstr_fd(fd, "exit: too many arguments\n");
		return (1);
	}
	else if (counter(args) == 1 && is_number(args[0]))
	{
		ft_putstr_fd(fd, "exit\n");
		if (!is_int(args[0]))
		{
			ft_putstr_fd(fd, args[0]);
			ft_putstr_fd(fd, ": numeric argument required\n");
			exit(255);
		}
		exit(ft_atoi(args[0]));
	}
	return (0);
}

int	ft_exit(char **args, int fd)
{
	if (!args[0])
	{
		printf("exit\n");
		exit(0);
	}
	if (!is_number(args[0]))
	{
		ft_putstr_fd(fd, "exit\n");
		ft_putstr_fd(fd, args[0]);
		ft_putstr_fd(fd, ": numeric argument required\n");
		exit(255);
	}
	if (code_is_number(args, fd) == 1)
		return (1);
	return (0);
}
