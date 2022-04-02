/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 06:04:27 by yhakkach          #+#    #+#             */
/*   Updated: 2022/04/02 21:21:38 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		printf("export: `%s': not a valid identifier \n", str);
		return (0);
	}
	i = 1;
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

//4 for ""=0
static char	*concat_var(char **var)
{
	char	*str;
	int		i;
	int		j;

	i = ft_strlen(var[0]);
	if (var[1])
		i += ft_strlen(var[1]);
	str = malloc(i + 1);
	i = 0;
	j = 0;
	while (var[0][j])
		str[i++] = var[0][j++];
	j = 0;
	if (var[1])
		str[i++] = '=';
	while (var[1] && var[1][j])
		str[i++] = var[1][j++];
	str[i] = 0;
	return (str);
}

static char	**export_arg(char **env, char **var)
{
	int		i;
	char	**new_env;

	i = -1;
	while (env[++i])
	{
		if (!ft_strchr(env[i], '='))
			return (env);
		if (!ft_strncmp(env[i], var[0], ft_strlen(var[0])))
		{
			free(env[i]);
			env[i] = concat_var(var);
			return (env);
		}
	}
	new_env = malloc(sizeof(char *) * (ft_arrlen((void **)env) + 2));
	if (!new_env)
		ft_error_exit(ERR_MALLOC);
	i = -1;
	while (env[++i])
		new_env[i] = env[i];
	new_env[i++] = concat_var(var);
	new_env[i] = NULL;
	free(env);
	return (new_env);
}

static int	msk_env_split(char c)
{
	static int	i;

	if (!c)
	{
		i = 0;
		return (0);
	}
	if (c == '=' && !i)
	{
		i = 1;
		return (1);
	}
	return (0);
}

int	ft_export(char **args)
{
	char	**env;
	char	**var;

	if (!(*args))
		ft_env(1);
	else
	{
		env = env_var(NULL);
		while (*args)
		{
			var = msk_split(*args, msk_env_split);
			if (!is_valid_identifier(var[0]))
				return (1);
			env = export_arg(env, var);
			env_var(env);
			args++;
		}
	}
	return (0);
}
