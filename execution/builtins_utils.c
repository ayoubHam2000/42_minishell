/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:08:57 by hbourkan          #+#    #+#             */
/*   Updated: 2022/04/15 20:31:41 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") || ft_strcmp(cmd, "pwd") || ft_strcmp(cmd, "env")
		|| ft_strcmp(cmd, "unset") || ft_strcmp(cmd, "export")
		|| ft_strcmp(cmd, "cd") || ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	execute_builtin(t_command **cmds, int i)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmds[i]->command, "echo"))
		status = ft_echo(cmds[i]->args, cmds[i]->fd[1]);
	else if (ft_strcmp(cmds[i]->command, "cd"))
		status = ft_cd(cmds[i]->args);
	else if (ft_strcmp(cmds[i]->command, "pwd"))
		status = ft_pwd(cmds[i]->fd[1]);
	else if (ft_strcmp(cmds[i]->command, "env"))
		status = ft_env(cmds[i]->args, 0, cmds[i]->fd[1]);
	else if (ft_strcmp(cmds[i]->command, "export"))
		status = ft_export(cmds[i]->args, cmds[i]->fd[1]);
	else if (ft_strcmp(cmds[i]->command, "unset"))
		status = ft_unset(cmds[i]->args, cmds[i]->fd[1]);
	else if (ft_strcmp(cmds[i]->command, "exit"))
		status = ft_exit(cmds[i]->args, cmds[i]->fd[1]);
	return (status);
}

int	ft_validvarname(int c, int c2)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_' || (c == '$' && c2 != '\0'))
		return (1);
	return (0);
}

int	check_vn(char *arg)
{
	char	*temp;
	int		i;

	i = 0;
	if (ft_strchr(arg, '='))
		temp = ft_substr(arg, 0, equal_position(arg));
	else
		temp = ft_strdup(arg);
	while (temp[i])
	{
		if (!ft_validvarname(temp[i], temp[i + 1])
			|| (temp[i] != '_' && !ft_isalpha(temp[i])))
			return (0);
		i++;
	}
	return (1);
}

int	equal_position(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}
