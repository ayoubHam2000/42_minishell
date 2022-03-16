/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:48:48 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/16 02:50:54 by yhakkach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_valid_identifier1(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		printf("export: `%s': not a valid identifier \n", str);
		return (0);
	}
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			printf("export: `%s': not a valid identifier \n", str);
			return (0);
		}
		i++;
	}
	return (1);
}


int		is_here(char	*str,char	**envp)
{
	int		i;

	i = 0;

	while (str[i])
	{
		if (!strncmp(envp[i], str, ft_strlen(str)))
			return (-1);		
		i++;
	}
	return (1);
}



char	**ft_unset(char **args, char **envp)
{
	int		i;
	int		j;
	char	**unse;
	int 	ii;

	ii = 0;
	i = 0;
	j = 0; 
	
	

	unse = ft_malloc(sizeof(char *) * (ft_arrlen((void **)envp)));
	if (!unse)
		return (0);
	while (args[ii])
	{
		while (envp[i])
		{
			if (strncmp(envp[i], args[ii], ft_strlen(args[ii])))
				unse[j++] = envp[i];
			else
			{
				i++;
				break ;
			}
			i++;
		}
		ii++;
	}
	unse[j] = 0;
	return (unse);
}
