/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 01:20:53 by yhakkach          #+#    #+#             */
/*   Updated: 2022/04/02 16:01:46 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_digits(char *arg)
{
	long long	i;

	i = 0;
	if (!arg)
		return (1);
	if (*arg == '-' || *arg == '+')
		arg++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	fttt_exit_error(char *arg)
{
	ft_error("exit: ");
	ft_error(arg);
	ft_error(": numeric argument required\n");
}

int	ft_exit(char **args)
{
	if (ft_arrlen((void **)args) == 0)
	{
		printf("exit\n");
		exit(0);
	}
	if (!ft_digits(args[0]) || !is_int(args[0]))
	{
		fttt_exit_error(args[0]);
		exit(-1);
	}
	if (ft_arrlen((void **)args) > 1)
	{
		ft_error("minishell: exit: too many arguments\n");
		return (1);
	}
	exit(ft_atoi(args[0]));
}
