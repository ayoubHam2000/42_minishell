/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 06:04:27 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/11 19:07:32 by yhakkach         ###   ########.fr       */
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

	if (!str)
		return (cmd);
	i = -1;
	j = 0;
	split = malloc(sizeof(char *) * (ft_arrlen(cmd) + 2));
	while (cmd[++i])
		split[i] = cmd[i];
	split[i++] = str;
	split[i] = 0;
	return (split);
}


int is_valid_identifier(char *str)
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

int ft_strcherche(char *str, char c)
{
	int i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
char	*verfy(char *str)
{
	int	i;
	char	**split;
	

	int index_equal = ft_strcherche(str,'=');
	if (index_equal == -1)
	{
		is_valid_identifier(str);
		return (0);
	}
	char *var_name = ft_substr(str,0,index_equal);
	if (is_valid_identifier(var_name))
		return (str);
	return (0);
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
			//printf("%s\n",args);
			split = envexport(envp, verfy(*args));
			args++;
		}
		// i = 0;
		// while ()
		return (split);
	}
}
