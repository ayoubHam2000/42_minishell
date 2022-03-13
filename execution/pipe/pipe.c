/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:11:53 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/13 10:28:19 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
static int	spa888wn_proc(int in, int out, t_command *cmd, char **envp)
{
	pid_t	pid;
	char	**args;

	pid = fork();
	if (pid == 0)
	{
		if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		args = get_args(cmd, envp);
		return (execve(args[0], args, envp));
	}
	return (pid);
}



int	fo888rk_pipes(int n, t_command **arrcmd, char **envp)
{
	int		i;
	int		in;
	int		fd [2];
	char	**args;

	i = 0;
	in = 0;
	while (i < n - 1)
	{
		pipe (fd);
		spawn_proc(in, fd[1], arrcmd[i], envp);
		close(fd[1]);
		in = fd[0];
		i++;
	}
	if (in != 0)
		dup2(in, 0);
	args = get_args(arrcmd[i], envp);
	return (execve(args[0], args, envp));
}
*/