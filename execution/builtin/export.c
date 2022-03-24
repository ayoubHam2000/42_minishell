/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 06:04:27 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/24 09:57:38 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_arrlenop(char **arr)
{
	int	res;

	res = 0;
	while (arr[res])
		res++;
	return (res);
}

void	printarray(char **array,int k)
{
	int	i;

	i = 0;
	if (k == 0)
	{
		while (array[i])
			printf("%s\n", array[i++]);
	}
	else
	{
		while (array[i])
			printf("declare -x %s\n", array[i++]);
	}
	
}

char	*copy_arg(char *s1)
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

char	**envexport(char **cmd, char *str)
{
	int		i;
	int		j;
	char	**split;

	if (!str)
		return (cmd);
	i = -1;
	j = 0;
	split = malloc(sizeof(char *) * (ft_arrlenop(cmd) + 2));
	if (!split)
		ft_error_exit(ERR_MALLOC);
	while (cmd[++i])
		split[i] = cmd[i];
	split[i++] = copy_arg(str);
	split[i] = 0;
	free(cmd);
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
		if (!ft_isalnum(str[i])&& str[i] != '_')
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
	int index_equal;
	index_equal = ft_strcherche(str,'=');
	if (index_equal == -1)
	{
		is_valid_identifier(str);
		return (0);
	}
	char *var_name = ft_substr(str, 0, index_equal);
	if (is_valid_identifier(var_name))
		return (str);
	return (0);
}


int			is_equal(char *str)
{
	int i;
	
	i = 0;

	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}



int		is_here(char *str, char **envp)
{

	int		i;
	char 	*s;

	s = ft_substr(str,0,is_equal(str));
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i],s,ft_strlen(s)))
		{
			return(i);
		}
		i++;
	}
	return (-1);
}



int	ft_export(char **args)
{
	int		i;
	char	**env;

	i = 0;
	env = env_var(NULL);
	if (!(*args))
	{
		printarray(env, 8);
	}
	else
	{
		while (args[i])
		{
			int idx_env = is_here(args[i],env);
			if (idx_env != -1)
			{
				env[idx_env] = copy_arg(args[i]);
			}
			else
				env = envexport(env, verfy(args[i]));
			i++;
		}
		env_var(env);
	}
	return (0);
}
