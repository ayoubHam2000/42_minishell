/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 01:22:58 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/15 22:20:36 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_var(char *str)
{
	char	*new;
	int		i;

	new = malloc(ft_strlen(str) + 1);
	if (!new)
		ft_error_exit(ERR_MALLOC);
	i = -1;
	while (str[++i])
		new[i] = str[i];
	new[i] = 0;
	return (new);
}

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
		copy_env[i] = copy_var(env[i]);
		i++;
	}
	copy_env[i] = NULL;
	return (copy_env);
}

char	**env_var(char **new_env)
{
	static char	**env;

	if (new_env)
	{
		env = new_env;
	}
	return (env);
}

static int	msk_env_split(char c)
{
	static int	i;

	if (!c)
	{
		i = 0;
	}
	else if (c == '=' && !i)
	{
		i = 1;
		return (1);
	}
	return (0);
}

char	*ft_getenv(char *var)
{
	char	**tmp;

	tmp = env_var(NULL);
	if (!tmp || !var)
		return (NULL);
	if (var[0] == '?' && var[1] == 0)
		return (ft_itoa(get_exit_status()));
	while (*tmp)
	{
		if (!ft_strncmp(var, *tmp,
				ft_strlen(ft_substr(*tmp, 0, equal_position(*tmp)))))
			return (msk_split(*tmp, msk_env_split)[1]);
		tmp++;
	}
	return (NULL);
}
