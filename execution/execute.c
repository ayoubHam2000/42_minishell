/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:48:32 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/24 20:48:23 by yhakkach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

void	env_cmd_path2(char **pathsplit, char *cmd, char *str, int i)
{	
	i = 0;
	while (pathsplit[i])
	{
		str = ft_strjoin(pathsplit[i++], "/");
		str = ft_strjoin(str, cmd);
		if (access(str, X_OK | F_OK) == 0)
			return (str);
	}
	printf(" %s: command not found \n", cmd);
	exit(127);
}

static char	*env_cmd_path(char *cmd)
{
	char	*path;
	char	**pathsplit;
	int		i;
	char	*str;
	char	**envp;

	i = 0;
	envp = env_var(NULL);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	path = envp[i] + 5;
	pathsplit = ft_split(path, ':');
	env_cmd_path2(pathsplit, cmd, str, i);
	return (NULL);
}

int	execute(t_command	**arrcmd)
{
	int	status;
	int	last_pid;
	int	ret;

	if (is_builtin(arrcmd[0]->command) && ft_arrlen((void **)arrcmd) == 1)
	{
		ret = exec_built_in(arrcmd[0]);
		du_exit_status(ret, 1);
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
