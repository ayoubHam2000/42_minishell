/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:11:53 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/24 20:48:46 by yhakkach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	spawn_proc(int in, int out, t_command *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (in != 0)
		{
			dup2(in, 0);
		}
		if (out != 1)
		{
			dup2(out, 1);
		}
		exec_cmd(cmd);
	}
	return (pid);
}

static int	fork_last(char *cmd, int redin, int fileout)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (redin != 0)
		{
			dup2(redin, 0);
		}
		if (fileout != 1)
		{
			dup2(fileout, 1);
		}
		exec_cmd(cmd);
		exit(0);
	}
	return (pid);
}

static void	fork_meddle(int *redin, int *redout, t_command *cmd)
{
	int		fd[2];
	int		filein;
	int		fileout;

	pipe(fd);
	filein = cmd->fd[0];
	fileout = cmd->fd[1];
	if (fileout != 1)
	{
		*redout = fileout;
		close(fd[1]);
		fd[1] = *redout;
	}
	if (filein != 0)
		*redin = filein;
	spawn_proc(*redin, fd[1], cmd);
	close(fd[1]);
	redin = fd[0];
}

int	fork_pipes(int n, t_command **arrcmd)
{
	int		i;
	int		redin;
	int		redout;
	int		filein;
	int		fileout;

	i = 0;
	filein = arrcmd[0]->fd[0];
	fileout = arrcmd[0]->fd[1];
	while (i < n - 1)
	{
		fork_meddle(&redin, &redout, arrcmd[i]);
		i++;
	}
	filein = arrcmd[i]->fd[0];
	fileout = arrcmd[i]->fd[1];
	if (filein != 0)
		redin = filein;
	return (fork_last(arrcmd[i], redin, fileout));
}
