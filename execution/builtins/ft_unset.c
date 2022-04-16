/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:08:17 by hbourkan          #+#    #+#             */
/*   Updated: 2022/04/15 23:04:26 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_keys(char *arg, char *s)
{
	char	*temp;

	if (ft_strchr(s, '='))
		temp = ft_substr(s, 0, equal_position(s));
	else
		temp = ft_strdup(s);
	if (ft_strcmp(temp, "_"))
		return (0);
	if (!check_vn(temp))
		return (0);
	if (ft_strcmp(arg, temp))
		return (1);
	return (0);
}

int	able_to_unset(char **args, char *s)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (compare_keys(args[i], s))
			return (0);
		i++;
	}
	return (1);
}

void	comparing(char **env, char *arg, int *counter)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (compare_keys(arg, env[i]))
			(*counter)++;
		i++;
	}
}

int	c_args2(char **args, char **env, int fd)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '=') || !check_vn(args[i]))
		{
			ft_putstr_fd(2, args[i]);
			ft_putstr_fd(2, ": not a valid identifier\n");
			i++;
			continue ;
		}
		if (ft_strcmp(args[i], "_"))
		{
			i++;
			continue ;
		}
		comparing(env, args[i], &counter);
		i++;
	}
	return (counter);
}

int	ft_unset(char **args, int fd)
{
	char	**env;
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	env = env_var(NULL);
	new_env = malloc(sizeof(char *) * (counter(env)
				- c_args2(args, env, fd) + 1));
	while (env[j])
	{
		if (!able_to_unset(args, env[j]))
		{
			j++;
			continue ;
		}
		new_env[i++] = env[j++];
	}
	new_env[i] = NULL;
	env_var(new_env);
	return (0);
}
