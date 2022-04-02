/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:38:52 by yhakkach          #+#    #+#             */
/*   Updated: 2022/04/02 18:17:55 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(int k)
{
	char	**array;
	int		i;

	i = 0;
	array = env_var(NULL);
	if (k == 0)
	{
		while (array[i] && ft_strchr(array[i], '='))
		{
			ft_print_out(array[i++]);
			ft_print_out("\n");
		}
	}
	else
	{
		while (array[i])
		{
			ft_print_out("declare -x ");
			ft_print_out(array[i++]);
			ft_print_out("\n");
		}
	}
}

int	ft_env(int type)
{
	print_env(type);
	return (0);
}
