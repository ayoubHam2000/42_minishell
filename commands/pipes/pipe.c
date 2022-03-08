/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:11:53 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/08 14:35:12 by yhakkach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct s_redt
{
	char	r_type;
	char	*file;
}	t_redt;

typedef struct s_command
{
	char	*command;
	char	**args;
	t_redt	**redt;
}	t_command;

char	**ft_split(char const *str, char c);

size_t	ft_strlen(const char *s);

char	*ft_substr(char const *s1, unsigned int start, size_t len);


char *ft_strjoin(char *str1, char *str2)
{
    int     i;
    int     j;
    char    *new;
    
    i = 0;
    j = 0;

    if(!str1 && !str2)
        return(0);
    new = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
    if(!new)
        return (0);

    while (str1[i])
        new[j++]= str1[i++];
    i = 0;
    while (str2[i])
        new[j++]=str2[i++];
    new[j] = '\0';
    return (new);
}

char    *path(char   **envp,char *cmd)
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
    path = envp[i] + 5;
    pathsplit = ft_split(path,':');
    
    i = 0;

    while(pathsplit[i])
    {
        str = ft_strjoin(ft_strjoin(pathsplit[i++],"/"),cmd);
        if (access(str, X_OK |F_OK) == 0)
          return (str);
    }
    return (NULL);
}

int
spawn_proc (int in, int out, t_command cmd,char **envp)
{
  pid_t pid;
  
  char *args[] = {"-la", NULL};

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
      return execve(path(envp,cmd.command),cmd.args,envp);
    }

  return pid;
}


int
fork_pipes (int n, t_command arrcmd[] ,char **envp)
{
  int i;
  pid_t pid;
  int in, fd [2];

  i = 0;
  in = 0;

  while (i < n - 1)
  {
      pipe (fd);
      spawn_proc (in, fd [1], arrcmd[i],envp);
      close (fd [1]);
      in = fd [0];
      i++;
  }
    
  if (in != 0)
    dup2 (in, 0);
  return execve(path(envp,arrcmd[i].command),arrcmd[i].args,envp);
}


int
main (int argc,char **argv,char **envp)
{

    t_command t[2];
  //   t[0].command = "ls";
  //  t[0].args = {"ls","-la",NULL};

  //   t[1].command = "ps";
  //   t[1].args ={"ps","-la",NULL};
    
  //   //t[2].command = "sleep";
  //   //t[2].args = {"sleep","5",NULL};

  return fork_pipes (2, t,envp);
}