/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:08:59 by hbourkan          #+#    #+#             */
/*   Updated: 2022/04/15 21:02:26 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_proc(t_command **cmds, int **pipefd,
	int nb_pipes, pid_t *childpid)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmds[j])
	{
		if (!cmds[j]->command)
		{
			get_overcmd(cmds, childpid);
			j++;
			continue ;
		}
		*childpid = fork();
		if (*childpid == -1)
			exit(1);
		else if (*childpid == 0)
		{
			redirec(cmds, pipefd, i, j);
			close_pipes(nb_pipes, pipefd);
			cmd_type(cmds, j, nb_pipes, pipefd);
		}
		i += 2;
		j++;
	}
}

int	single_process(t_command **cmds)
{
	int		status;
	pid_t	childpid;

	if (is_builtin(cmds[0]->command))
		status = execute_builtin(cmds, 0);
	else
	{
		childpid = fork();
		if (childpid == -1)
			exit(1);
		else if (childpid == 0)
			executer2(cmds, 0);
		waitpid(childpid, &status, 0);
	}
	return (status);
}

int	multiple_process(t_command **cmds, int nb_pipes)
{
	t_status	s;
	pid_t		childpid;
	int			*pipefd;
	int			i;

	i = 0;
	pipefd = malloc(sizeof(int) * (nb_pipes * 2));
	if (!pipefd)
		return (1);
	open_pipes(nb_pipes, &pipefd);
	child_proc(cmds, &pipefd, nb_pipes, &childpid);
	close_pipes(nb_pipes, &pipefd);
	while (i <= nb_pipes)
	{
		s.res = waitpid(-1, &s.status, 0);
		if (s.res == childpid || childpid == -1)
				s.last_status = s.status;
		i++;
	}
	free(pipefd);
	return (s.last_status);
}

void	execute(t_command **cmds)
{
	int	nb_pipes;
	int	exit_status;

	nb_pipes = ft_arrlen((void **)cmds) - 1;
	if (nb_pipes <= 0)
	{
		if (!cmds[0]->command)
		{
			du_exit_status(1, 1);
			return ;
		}
		else
		{
			exit_status = single_process(cmds);
			if (is_builtin(cmds[0]->command))
			{
				du_exit_status(exit_status, 1);
				return ;
			}
		}
	}
	else
		exit_status = multiple_process(cmds, nb_pipes);
	set_exit_status(exit_status);
}
