/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:38:52 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/24 21:10:17 by aben-ham         ###   ########.fr       */
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
		while (array[i])
			printf("%s\n", array[i++]);
	}
	else
	{
		while (array[i])
			printf("declare -x %s\n", array[i++]);
	}
}

int	ft_env(int type)
{
	print_env(type);
	return (0);
}
