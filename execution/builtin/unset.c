/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:48:48 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/16 20:00:26 by yhakkach         ###   ########.fr       */
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



int	ft_unset(char **args)
{
	int		i;
	int		j;
	char	**unse;
	int 	ii;
	char	**envp;

	ii = 0;
	i = 0;
	j = 0; 
	envp = env_var(NULL);
	unse = malloc(sizeof(char *) * (ft_arrlen((void **)envp)));
	if (!unse)
		ft_error_exit(ERR_MALLOC);
	unse[0] = NULL;
	while (args[ii])
	{
		if (is_valid_identifier1(args[ii]))
		{
			while (envp[i])
			{
				if (!strncmp(envp[i], args[ii], ft_strlen(args[ii])))
					i++;
				unse[j++] = envp[i++];
			}
		}
		ii++;
	}
	unse[j] = NULL;
	if (unse[0] == NULL)
		unse = envp;
	env_var(unse);
	return (0);
}
