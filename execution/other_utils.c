/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:30:07 by hbourkan          #+#    #+#             */
/*   Updated: 2022/04/16 00:23:36 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	counter(char **arr)
{
	int	counter;

	counter = 0;
	while (arr[counter])
		counter++;
	return (counter);
}

void	get_overcmd(t_command **cmds, int *childpid)
{
	*childpid = fork();
	if (*childpid == -1)
	{
		perror("Fork failed");
		exit(1);
	}
	else if (*childpid == 0)
		exit(1);
}

void	cmd_type(t_command **cmds, int j, int nb_pipes, int **pipefd)
{
	int	status;

	status = 0;
	if (is_builtin(cmds[j]->command))
	{
		status = execute_builtin(cmds, j);
		exit(status);
	}
	else
		exec_multiple(cmds, j, nb_pipes, pipefd);
}

void	exec_single(t_command **cmds, int j)
{
	char	*path;
	char	**args;

	path = getpath(cmds[j]->command);
	if (!path)
	{
		ft_putstr_fd(2, "Command not found\n");
		exit(127);
	}
	args = join_args(cmds, j);
	in_out_red(cmds[j]->fd[0], cmds[j]->fd[1]);
	if (execve(path, args, env_var(NULL)) == -1)
	{
		perror("");
		exit(127);
	}
}

void	exec_multiple(t_command **cmds, int j, int nb_pipes, int **pipefd)
{
	char	*path;
	char	**args;

	path = getpath(cmds[j]->command);
	if (!path)
	{
		ft_putstr_fd(2, "Command not found\n");
		exit(127);
	}
	args = join_args(cmds, j);
	in_out_red(cmds[j]->fd[0], cmds[j]->fd[1]);
	close_pipes(nb_pipes, pipefd);
	if (execve(path, args, env_var(NULL)) == -1)
	{
		perror("");
		exit(127);
	}
}
