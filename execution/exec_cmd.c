/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:27:15 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/25 15:34:10 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**add_arg_0(char **args, char *arg0)
{
	char	**res;
	int		i;

	i = 0;
	while (args[i])
		i++;
	res = malloc(sizeof(char *) * (i + 2));
	i = 0;
	res[i] = arg0;
	while (args[i])
	{
		res[i + 1] = args[i];
		i++;
	}
	res[i + 1] = NULL;
	return (res);
}

static char	*env_cmd_path(char *cmd)
{
	char	**pathsplit;
	int		i;
	char	*str;

	pathsplit = ft_split(ft_getenv("PATH"), ':');
	i = 0;
	while (pathsplit && pathsplit[i])
	{
		str = ft_strjoin(pathsplit[i], "/");
		str = ft_strjoin(str, cmd);
		if (access(str, X_OK | F_OK) == 0)
			return (str);
		i++;
	}
	printf(" %s: command not found \n", cmd);
	exit(127);
}

static char	*get_cmd_path(char *command)
{
	if (*command == '/')
		return (command);
	else if (ft_strchr(command, '/'))
	{
		command = ft_strjoin("/", command);
		return (ft_strjoin(get_path(), command));
	}
	else
		return (env_cmd_path(command));
}

void	exec_cmd(t_command *cmd)
{
	char	*path;
	char	**args;

	if (cmd->command == NULL)
		return ;
	else if (is_builtin(cmd->command))
	{
		exit(exec_built_in(cmd));
	}
	else
	{
		path = get_cmd_path(cmd->command);
		if (!path)
			return ;
		args = add_arg_0(cmd->args, path);
		execve(args[0], args, env_var(NULL));
	}
}
