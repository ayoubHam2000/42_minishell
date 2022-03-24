/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 06:04:27 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/24 22:06:33 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*verfy(char *str)
{
	int		index_equal;
	char	*var_name;

	index_equal = ft_strcherche(str, '=');
	if (index_equal == -1)
	{
		is_valid_identifier(str);
		return (0);
	}
	var_name = ft_substr(str, 0, index_equal);
	if (is_valid_identifier(var_name))
		return (str);
	return (0);
}

int	is_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	is_here(char *str, char **envp)
{
	int		i;
	char	*s;

	s = ft_substr(str, 0, is_equal(str));
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], s, ft_strlen(s)))
			return (i);
		i++;
	}
	return (-1);
}

char	**exportwhile(char **args, int i, int idx_env)
{
	char	**env;

	env = env_var(NULL);
	while (args[i])
	{
		idx_env = is_here(args[i], env);
		if (idx_env != -1)
			env[idx_env] = copy_arg(args[i]);
		else
		{
			env = envexport(env, verfy(args[i]));
			if (!env)
				return (NULL);
		}
		i++;
	}
	return (env);
}

int	ft_export(char **args)
{
	int		i;
	char	**env;
	int		idx_env;

	i = 0;
	idx_env = 0;
	if (!(*args))
		ft_env(1);
	else
	{
		env = exportwhile(args, i, idx_env);
		if (!env)
			return (1);
		env_var(env);
	}
	return (0);
}
