/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:27:15 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/24 22:12:24 by aben-ham         ###   ########.fr       */
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

int	is_builtin(char *str)
{
	const char	*built_in[] = {"cd", "pwd", "echo", "exit", \
	"export", "unset", "env", NULL};
	int			i;

	i = 0;
	while (built_in[i])
	{
		if (str && ft_strcmp(str, (char *)built_in[i]))
			return (1);
		i++;
	}
	return (0);
}

int	exec_built_in(t_command *command)
{
	int	i;

	i = 0;
	if (ft_strcmp(command->command, "cd"))
		i = ft_cd(command->args);
	else if (ft_strcmp(command->command, "pwd"))
		i = ft_pwd();
	else if (ft_strcmp(command->command, "echo"))
		i = ft_echo(command->args);
	else if (ft_strcmp(command->command, "exit"))
		ft_exit(command->args);
	else if (ft_strcmp(command->command, "export"))
		i = ft_export(command->args);
	else if (ft_strcmp(command->command, "unset"))
		i = ft_unset(command->args);
	else if (ft_strcmp(command->command, "env"))
	i = ft_env(0);
	return (i);
}

void	exec_cmd(t_command *cmd)
{
	char	*path;
	char	**args;

	if (cmd->command == NULL)
		return ;
	else if (is_builtin(cmd->command))
	{
		exec_built_in(cmd);
		exit(13);
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

char	*get_cmd_path(char *command)
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
