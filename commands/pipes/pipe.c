/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:11:53 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/09 13:19:31 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char    *path(char **envp, char *cmd)
{
    char    *path;
    char    **pathsplit;
    int     i;
    char    *str;

    i = 0;
    while (envp[i])
    {
        if (!strncmp(envp[i], "PATH=", 5))
            break ;
        i++;
    }
    if (!envp[i])
      return (NULL);
    path = envp[i] + 5;
    pathsplit = ft_split(path,':');
    i = 0;
    while(pathsplit[i])
    {
        str = ft_strjoin(pathsplit[i++],"/");
        str = ft_strjoin(str , cmd);
        if (access(str, X_OK | F_OK) == 0)
          return (str);
    }
    return (NULL);
}

static char  **get_args(t_command *cmd, char **envp)
{
  char  **res;
  int   i;

  i = 0;
  while (cmd->args[i])
	i++;
  res = malloc(sizeof(char *) * (i + 2));
  i = 0;
  res[i] = path(envp, cmd->command);
  while (cmd->args[i])
  {
	  res[i + 1] = cmd->args[i];
	  i++;
  }
  res[i + 1] = NULL;
  return (res);
}

static int spawn_proc (int in, int out, t_command *cmd,char **envp)
{
  	pid_t	pid;
  	char	**args;

	if ((pid = fork ()) == 0)
	{
		if (in != 0)
		{
			dup2 (in, 0);
			close (in);
		}
		if (out != 1)
		{
			dup2 (out, 1);
			close (out);
		}
		args = get_args(cmd, envp);
		return execve(args[0] , args,envp);
	}
  	return pid;
}

int fork_pipes (int n, t_command **arrcmd ,char **envp)
{
	int i;
	pid_t pid;
	int in, fd [2];
	char	**args;

	i = 0;
	in = 0;

	while (i < n - 1)
	{
		pipe (fd);
		spawn_proc (in, fd[1], arrcmd[i],envp);
		close (fd [1]);
		in = fd [0];
		i++;
	}
	if (in != 0)
	dup2 (in, 0);
	args = get_args(arrcmd[i], envp);
	return execve(args[0], args, envp);
}
