/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:08:37 by hbourkan          #+#    #+#             */
/*   Updated: 2022/04/15 23:06:44 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_export_env(char **env, int fd)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd(fd, "declare -x ");
		if (ft_strchr(env[i], '='))
		{
			ft_putstr_fd(fd, ft_substr(env[i], 0, equal_position(env[i]) + 1));
			write(fd, "\"", 1);
			ft_putstr_fd(fd, env[i] + equal_position(env[i]) + 1);
			write(fd, "\"\n", 2);
		}
		else
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

char	*ft_copy(char *s1)
{
	char	*s2;
	size_t	s1_len;

	s1_len = ft_strlen((char *)s1);
	s2 = malloc(s1_len + 1);
	if (!s2)
		ft_error_exit(ERR_MALLOC);
	ft_strlcpy(s2, s1, s1_len + 1);
	return (s2);
}

char	**new_env(char **env, char *arg)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc((counter(env) + 2) * (sizeof(char *)));
	if (!tmp)
		ft_error_exit(ERR_MALLOC);
	while (env[i])
	{
		tmp[i] = env[i];
		i++;
	}
	tmp[i++] = ft_copy(arg);
	tmp[i] = NULL;
	free(env);
	return (tmp);
}

char	**exporting_arg(char **env, char *arg)
{
	char	**tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strcmp(ft_substr(env[i], 0, equal_position(env[i]))
				, ft_substr(arg, 0, equal_position(arg))))
		{
			if (ft_strchr(arg, '='))
			{
				free(env[i]);
				env[i] = ft_copy(arg);
			}
			return (env);
		}
		i++;
	}
	return (new_env(env, arg));
}

int	ft_export(char **args, int fd)
{
	char	**env;
	int		i;

	i = 0;
	env = env_var(NULL);
	if (counter(args) == 0)
		return (print_export_env(env, fd));
	while (args[i])
	{
		if (check_vn(args[i]))
			env = exporting_arg(env, args[i]);
		else
		{
			ft_putstr_fd(2, args[i]);
			ft_putstr_fd(2, ": not a valid identifier\n");
		}
		i++;
	}
	env_var(env);
	return (0);
}
