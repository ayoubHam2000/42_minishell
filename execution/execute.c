/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:48:32 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/25 16:47:49 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	execute(t_command	**arrcmd)
{
	int	status;
	int	last_pid;
	int	ret;

	if (is_builtin(arrcmd[0]->command) && ft_arrlen((void **)arrcmd) == 1)
	{
		get_fd_out(arrcmd[0]->fd[1]);
		ret = exec_built_in(arrcmd[0]);
		du_exit_status(ret, 1);
		get_fd_out(0);
		return (ret);
	}
	else
	{
		last_pid = fork_pipes(ft_arrlen((void **)arrcmd), arrcmd);
		ret = waitpid(-1, &status, 0);
		while (ret != 0 && ret != -1)
		{
			if (ret == last_pid)
				set_exit_status(status);
			ret = waitpid(-1, &status, 0);
		}
		return (ret);
	}
}
