/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 01:47:56 by yhakkach          #+#    #+#             */
/*   Updated: 2022/02/28 20:54:37 by yhakkach         ###   ########.fr       */
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


///////////////////////////////////

int	ft_arraylen(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
	{
		i++;
	}
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}


int	ft_digits(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (1);
	while (cmd[i] && cmd)
	{
		if (!ft_isdigit(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_cmd(char **cmd)
{
	if (ft_arraylen(cmd) > 2)
	{
		printf("exit: too many arguments\n");
		return ;
	}
	printf("exit\n");
	if (!ft_digits(cmd[1]))
	{
		printf("exit: %s: numeric argument required\n",cmd[1]);
		exit(2);
	}
	if (!cmd[1])
		exit(EXIT_SUCCESS);
	else
		exit(atoi(cmd[1]));
}
//////////////////////////////////






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
//////////////////////
////////pwd///////
void  pwd()
{
    char    cwd[1024];
    getcwd(cwd,sizeof(cwd));
    printf("%s\n",cwd);
}
//////////////////pwd
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
////////////////cd//////
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
////////////////////////////////

////////////////////////////////
void    cdtest(char *path)
{
    char **plit;

    plit = ft_split(path,' ');
    if(!plit)
        return ;
    cd(plit);
}
/////////////////////////////////
void    exitcmd(char *path)
{
    char **plit;

    plit = ft_split(path,' ');
    if(!plit)
        return ;
    exit_cmd(plit);
}


void    env(char **cmd)
{
    int     i;

    i = 0;
    // if(ft_arraylen(command_buff) > 0)
    // {
    //      printf("env : error\n");
    //      return ;
    // }
    while(cmd[i])
        printf("%s\n",cmd[i++]);
}

///////////////////////////// Export /////////////////////////////////////////////////////////////
char        **to(char **envp)

{
    
    int     i;
    int     j;
    char    **split;
    int     n;
    i = -1;
    j = 0;

    n = ft_arraylen(envp);
    split = malloc(sizeof(char *) * (n  + 1));
    if (!split)
        return (NULL);
    while(envp[++i])
        split[i] = envp[i];
    split[i] = 0;
    return (split);
}
void printarray(char **array)

{
    int i;

    i = 0;
    while(array[i])
        printf("%s\n",array[i++]);
}

char    **envexport(char **cmd,char *str)
{
    int     i;
    int     j;
    char    **split;
    i = -1;
    j = 0;
    
    split = malloc(sizeof(char *) * (ft_arraylen(cmd) + 2));
    if (!split)
        return cmd;
    while(cmd[++i])
        split[i]=cmd[i]; 
    if(str)
        split[i++] = str;
    split[i] = 0;
    free(cmd);
    return (split);
}

char            *verfy(char *str)
{
    int         i;
    int         control;

    i = 0;
    control = 0;

     if (str[i] == '=')
    {
        printf("export: `%s': not a valid identifier \n",str);
        return (NULL);
    }
    while (str[i])
    {
        if(str[i] == ' ')
            control++;
        i++;
    }
    if (control != 0)
    {
        printf("export: `%s': not a valid identifier \n",str);
        return (NULL);
    }
            
    return (str);
}

char    **export(char * cmd,char **envp)
{
    char **split;
    char *str;
    int i;
    i = 1;

    if(!strncmp(cmd,"export",ft_strlen(cmd)))
    {
        printarray(envp);
        return (envp);
    }            
    else 
    {
        split = ft_split(cmd,' ');
        if(!split)
            return (envp);
        if(ft_arraylen(split) > 1)
        {
            while (i < ft_arraylen(split))
                envp = envexport(envp,verfy(split[i++]));
        }
        return (envp);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char           **unset(char *cmd,char   **envp)
{

        char **unse;
        int     i;
        int     j;
        char    **split;
        char    **tan;
        
        tan = malloc(sizeof(char *) * ft_arraylen(envp) + 1);
        
        i = 0;
        j = 0;
            unse = to(envp);
            split = ft_split(cmd,' ');
            
         while (i < ft_arraylen(unse))
         {  
             if(strcmp(unse[i],split[i]))
                i++;
                    tan[i++] = unse[j++];
         } 
         tan[i] = "\0";
    
    return (tan);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////







int     main(int argc,char **argv,char **envp)
{

    char  *username;
    pid_t   id;
    char    **join;
    join = to(envp);
    username =getenv("USER");
    printf(" ***** SHELL : %s *****\n",username);
    printf("\n");
    while(1)
    {
        command_buff =readline(" Hakkache  minishell  >  ");
        if (strlen(command_buff) > 0)
            add_history(command_buff);
        if (!strcmp(command_buff,"exit"))
                exit(0);
        else if(!strncmp(command_buff,"cd",2))
                cdtest(command_buff);
        else if(!strncmp(command_buff,"pwd",strlen(command_buff)))
                pwd();
        else if (!strncmp(command_buff,"exit",4))
                exitcmd(command_buff);
        else if (!strncmp(command_buff,"env",strlen(command_buff)))
                env(envp);
        else if(!strncmp(command_buff,"export",6))
                join = export(command_buff,join);
        else if(!strncmp(command_buff,"unset",5))
                join=unset(command_buff,join);
        else
            execute(path(envp,command_buff),envp);
    }
}

