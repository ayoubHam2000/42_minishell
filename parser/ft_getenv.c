/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 01:22:58 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/16 03:06:49 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_copy_env(char **env)
{
	char	**copy_env;
	size_t	i;

	copy_env = malloc(sizeof(char *) * (ft_arrlen((void **)env) + 1));
	if (!copy_env)
		ft_error_exit(ERR_MALLOC);
	i = 0;
	while (env[i])
	{
		copy_env[i] = env[i];
		i++;
	}
	copy_env[i] = NULL;
	return (copy_env);
}

char	**env_var(char **new_env)
{
	static char **env;

	if (new_env)
		env = new_env;
	return (env);
}

char	*ft_getenv(char *var)
{
	char	**tmp;

	tmp = env_var(NULL);
	if (!tmp || !var)
		return (NULL);
	while (*tmp)
	{
		if (!ft_strncmp(var, *tmp, ft_strlen(var)))
			return (ft_split(*tmp, '=')[1]);
		tmp++;
	}
	return (NULL);
}
