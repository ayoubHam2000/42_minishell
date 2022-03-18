/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 01:20:53 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/18 02:57:35 by yhakkach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_digits(char *arg)
{
	long long	i;

	i = 0;
	if (!arg)
		return (1);
	while (arg[i] && arg)
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **args)
{
	if (ft_arrlen((void **)args) > 1)
	{
		printf("exit: too many arguments");
		return ;
	}
	printf("exit\n");
	if (!ft_digits(args[0]))
	{
		printf("exit: %s: numeric argument required", args[0]);
		exit(2);
	}
	if ((long long)ft_atoi(args[0]) > 9223372036854775807)
	{
		printf("exit: %s: numeric argument required", args[0]);
		exit(2);
	}
	if ((long long)ft_atoi(args[0]) < (-9223372036854775807 - 1))
	{
		printf("exit: %s: numeric argument required", args[0]);
		exit(2);
	}
	if (!args[0])
		exit(EXIT_SUCCESS);
	else
		exit(atoi(args[0]));
}
