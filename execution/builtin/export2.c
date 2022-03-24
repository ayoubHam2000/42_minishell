/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:18:55 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/24 22:11:09 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	split = malloc(sizeof(char *) * (ft_arrlen((void **)cmd) + 2));
	if (!split)
		ft_error_exit(ERR_MALLOC);
	while (cmd[++i])
		split[i] = cmd[i];
	split[i++] = copy_arg(str);
	split[i] = 0;
	free(cmd);
	return (split);
}

int	is_valid_identifier(char *str)
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

int	ft_strcherche(char *str, char c)
{
	int	i;

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
