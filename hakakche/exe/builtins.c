/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 01:47:56 by yhakkach          #+#    #+#             */
/*   Updated: 2022/02/25 04:40:11 by yhakkach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>

char    *command_buff;

char	**ft_split(char const *str, char c);

size_t	ft_strlen(const char *s);


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


//////// path
char    *path(char   **envp,char *cmd)
{
    char    *path;
    char    **pathsplit;
    int     i;
    char    *str;

    i = 0;
    path = envp[6] + 5;

    pathsplit = ft_split(path,':');

    while(pathsplit[i])
    {
        str = ft_strjoin(ft_strjoin(pathsplit[i++],"/"),cmd);
        if (access(str, X_OK |F_OK) == 0)
            return (str);
    }
    return (NULL);
}

void  pwd()
{
    char    cwd[1024];
    getcwd(cwd,sizeof(cwd));
    printf("%s\n",cwd);
}

void    execute(char *path, char **envp)
{
    pid_t   id;

    id = fork();
    char    *argVec[] = {path,NULL};
    if (id == 0)
    {
        execve(path,argVec,envp);
    }
    wait(NULL);
}

void	cd(char **cmd)
{
	char	*path;
	
	if (cmd[2] && cmd[1])
	{
		printf("cd: too many arguments\n");
		return ;
	}
	if (!cmd[1])
		path = getenv("HOME");
	else
		path = cmd[1];
	if (path && path[0] == '~')
		path = getenv("HOME"); //change
		
	//  else if (path && path[0] == '.')
	//  		chdir("..");
	if (path && path[0] == '-' && !path[1])
	{
		path = getenv("OLDPWD");
		printf("%s\n", path);
	}
	if (chdir(path) < 0)
	{
		printf("cd: chdir error: %s\n", path);
		return ;
	}
}



void    cdtest(char *path)
{
    char **plit;

    plit = ft_split(path,' ');
    cd(plit);
}

int     main(int argc,char **argv,char **envp)
{

    char  *username;
    pid_t   id;


    username =getenv("USER");
    printf(" ***** SHELL : %s *****\n",username);
    printf("\n");
    while(1)
    {
        command_buff =readline(" minishell >  ");
        if (strlen(command_buff) > 0)
            add_history(command_buff);
        if (!strcmp(command_buff,"exit"))
                exit(0);
        else if(!strncmp(command_buff,"cd",2))
                cdtest(command_buff);
        else if(!strncmp(command_buff,"pwd",3))
                pwd();
        else if
        else
            execute(path(envp,command_buff),envp);
        
    }
}

