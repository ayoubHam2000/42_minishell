/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:09:05 by hbourkan          #+#    #+#             */
/*   Updated: 2022/04/15 01:22:08 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_out_red(int input, int output)
{
	if (dup2(input, STDIN) == -1)
	{
		perror("Dup failed");
		exit(1);
	}
	if (dup2(output, STDOUT) == -1)
	{
		perror("Dup failed");
		exit(1);
	}
}

void	redirec(t_command **cmds, int **pipefd, int i, int j)
{
	if (i == 0)
	{
		if (cmds[j]->fd[1] == STDOUT)
			in_out_red(cmds[j]->fd[0], (*pipefd)[i + 1]);
		else
			in_out_red(cmds[j]->fd[0], cmds[j]->fd[1]);
	}
	else if (cmds[j + 1] == NULL)
	{
		if (cmds[j]->fd[0] == STDIN)
			in_out_red((*pipefd)[i - 2], cmds[j]->fd[1]);
		else
			in_out_red(cmds[j]->fd[0], cmds[j]->fd[1]);
	}
	else
	{
		if (cmds[j]->fd[0] == STDIN && cmds[j]->fd[1] == STDOUT)
			in_out_red((*pipefd)[i - 2], (*pipefd)[i + 1]);
		else if (cmds[j]->fd[0] == STDIN)
			in_out_red((*pipefd)[i - 2], cmds[j]->fd[1]);
		else
			in_out_red(cmds[j]->fd[0], (*pipefd)[i + 1]);
	}
}

void	open_pipes(int nb_pipes, int **pipefd)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(*pipefd + i * 2) == -1)
		{
			perror("Failed to pipe");
			exit(1);
		}
		i++;
	}
}

void	close_pipes(int nb_pipes, int **pipefd)
{
	int	i;

	i = 0;
	while (i < nb_pipes * 2)
	{
		if (close((*pipefd)[i++]) == -1)
		{
			perror("Close failed");
			exit(1);
		}
	}
}
