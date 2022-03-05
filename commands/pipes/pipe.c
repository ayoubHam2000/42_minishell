/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:11:53 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/05 01:40:43 by yhakkach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

// typedef struct s_command
// {
// 	char	*command;
// 	char	**args;
// 	t_redt	**redt;
// }	t_command;


struct     command
{
    const   char **argv;
};

int
spawn_proc (int in, int out, struct command *cmd, char **envp)
{
  pid_t pid;

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
      return execve (cmd->argv [0], (char * const *)cmd->argv,envp);
    }

  return pid;
}


int
fork_pipes (int n, struct command *cmd,char **envp)
{
  int i;
  pid_t pid;
  int in, fd [2];

  in = 0;

  while (i < n - 1)
  {
      pipe (fd);
      spawn_proc (in, fd [1], cmd + i,envp);
      close (fd [1]);
      in = fd [0];
      i++;
  }
    
  if (in != 0)
    dup2 (in, 0);

    printf("%s",cmd[i].argv[0]);
  return execve (cmd [i].argv [0], (char * const *)cmd [i].argv,envp);
}


int
main (int  argc,char **argv,char **envp)
{
  const char *ls[] = { "cat", "file.txt", 0 };
  const char *ps[] = { "ps", "-la", 0 };
  
  struct command cmd [] = { {ls},{ps}};

  return fork_pipes (2, cmd,envp);
}