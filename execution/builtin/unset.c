/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:48:48 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/11 20:45:10 by yhakkach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_unset(char **args, char **envp)
{
	int		i;
	int		j;
	char	**unse;

	i = 0;
	j = 0;

	unse = ft_malloc(sizeof(char *) * (ft_arrlen(envp) - 1));
	if (unse)
		return (0);
	while (envp[i])
	{
		if (!strncmp(envp[i], args[1], ft_strlen(args[1])))
			i++;
		unse[j++] = envp[i++];
	}
	unse[j] = 0;
	return (unse);  
}
