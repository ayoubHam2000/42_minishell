/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:48:48 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/10 18:52:36 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_unset(char *args, char **envp)
{
	int		i;
	int		j;
	char	**split;
	char	**unse;

	i = 0;
	j = 0;
	split = ft_split(args, ' ');
	unse = ft_malloc(sizeof(char *) * (ft_arrlen(envp) - 1));
	while (envp[i])
	{
		if (!strncmp(envp[i], split[1], ft_strlen(split[1])))
			i++;
		unse[j++] = envp[i++];
	}
	unse[j] = 0;
	return (unse);  
}
