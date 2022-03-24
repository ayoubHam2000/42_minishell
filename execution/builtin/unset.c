/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:48:48 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/24 22:11:41 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier1(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		printf("unset: `%s': not a valid identifier \n", str);
		return (0);
	}
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			printf("unset: `%s': not a valid identifier \n", str);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	unset_vars(char **args, char **unse, char **envp)
{
	int	i;
	int	j;
	int	z;

	i = 0;
	z = 0;
	while (envp[i])
	{
		j = 0;
		while (args[j])
		{
			if (!strncmp(envp[i], args[j], ft_strlen(args[j])))
				break ;
			j++;
		}
		if (j == ft_arrlen((void **)args))
		{
			unse[z] = envp[i];
			z++;
		}
		else
			free(envp[i]);
		i++;
	}
	return (z);
}

int	ft_unset(char **args)
{
	char	**unse;
	char	**envp;
	int		i;

	i = 0;
	while (args[i])
	{
		if (!is_valid_identifier1(args[i]))
			return (2);
		i++;
	}
	envp = env_var(NULL);
	unse = malloc(sizeof(char *) * (ft_arrlen((void **)envp)));
	if (!unse)
		ft_error_exit(ERR_MALLOC);
	i = unset_vars(args, unse, envp);
	unse[i] = NULL;
	free(envp);
	env_var(unse);
	return (0);
}
