/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:08:41 by hbourkan          #+#    #+#             */
/*   Updated: 2022/04/15 18:19:41 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_opt(char *arg)
{
	int	i;

	i = 1;
	if (ft_strncmp(arg, "-n", 2))
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	skip_options(char **args, int *i)
{
	int	j;

	j = 1;
	while (args[j])
	{
		if (args[j] && check_opt(args[j]))
			(*i)++;
		j++;
	}
}

void	echoing_args(char *arg, int flag, int fd)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (flag == 1 && arg[i] == '\n')
			break ;
		if (arg[i] == '$' && arg[i] == '?')
			ft_putstr_fd(fd, ft_getenv("?"));
		write(fd, &arg[i], 1);
		i++;
	}
}

int	ft_echo(char **args, int fd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (args[i] && check_opt(args[i]))
	{
		flag = 1;
		i++;
	}
	if (flag == 1)
		skip_options(args, &i);
	while (args[i])
	{
		echoing_args(args[i], flag, fd);
		ft_putstr_fd(fd, " ");
		i++;
	}
	if (flag == 0)
		ft_putstr_fd(fd, "\n");
	return (0);
}
