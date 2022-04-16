/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:09:03 by hbourkan          #+#    #+#             */
/*   Updated: 2022/04/15 17:17:35 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_path(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	s = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i++] = '/';
	while (s2[j])
		s[i++] = s2[j++];
	s[i] = '\0';
	return (s);
}

char	*return_pathname(char **temp, char *cmd)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (cmd);
		i++;
	}
	return (NULL);
}

char	*getpath(char *cmd)
{
	char	**temp;
	char	*pathname;
	char	*value;
	int		i;

	i = 0;
	value = ft_getenv("PATH");
	if (!value)
		return (cmd);
	temp = ft_split(value, ':');
	if (!temp)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (return_pathname(temp, cmd));
	while (temp[i])
	{
		pathname = ft_strjoin_path(temp[i], cmd);
		if (access(pathname, F_OK | X_OK) == 0)
			return (pathname);
		free(pathname);
		i++;
	}
	return (NULL);
}

char	**join_args(t_command **cmds, int index)
{
	char	**joined_cmds;
	int		i;
	int		j;

	i = 0;
	j = 0;
	joined_cmds = malloc(sizeof(char *) * (get_cmds_nb(cmds[index]->args) + 1));
	joined_cmds[i++] = cmds[index]->command;
	while (cmds[index]->args[j])
		joined_cmds[i++] = cmds[index]->args[j++];
	joined_cmds[i] = NULL;
	return (joined_cmds);
}

int	get_cmds_nb(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
			i++;
	}
	return (i + 1);
}
