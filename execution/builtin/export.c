/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 06:04:27 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/10 15:51:53 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**to(char **envp)
{
	char	**split;
	int		i;
	int		j;
	int		n;

	i = -1;
	j = 0;
	n = ft_arrlen(envp);
	split = ft_malloc(sizeof(char *) * (n + 1));
	while (envp[++i])
		split[i] = envp[i];
	split[i] = 0;
	return (split);
}

void	printarray(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		printf("%s\n", array[i++]);
}

char	**envexport(char **cmd, char *str)
{
	int		i;
	int		j;
	char	**split;

	i = -1;
	j = 0;
	split = ft_malloc(sizeof(char *) * (ft_arrlen(cmd) + 2));
	while (cmd[++i])
		split[i] = cmd[i];
	split[i++] = str;
	split[i] = 0;
	return (split);
}

char	*verfy(char *str)
{
	int	i;
	int	control;

	i = 0;
	control = 0;
	if (str[i] == '=')
	{
		printf("export: `%s': not a valid identifier \n", str);
		return (0);
	}
	while (str[i])
	{
		if (str[i] == ' ')
			control++;
		i++;
	}
	if (control != 0)
	{
		printf("export: `%s': not a valid identifier \n", str);
		return (0);
	}
	return (str);
}

char	**ft_export(char **args, char **envp)
{
	char	**split;
	int		i;

	if (!(*args))
	{
		printarray(envp);
		return (envp);
	}
	else
	{
		while (*args)
		{
			envp = envexport(envp, verfy(*args));
			args++;
		}
		return (envp);
	}
}
