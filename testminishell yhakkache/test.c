
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

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
    printf("%s",cwd);
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

void    echoshell(char  *command_buff)
{
    char **split;
    int i = 1;
    split = ft_split(command_buff,' ');

    while (split[i])
        printf("%s",split[i++]);
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
        //pwd();
        command_buff =readline("minishell >  ");
        if (strlen(command_buff) > 0)
            add_history(command_buff);
        if (!strcmp(command_buff,"exit"))
                exit(0);
        else if (!strncmp(command_buff,"echo",4))   
                echoshell(command_buff);
        else
            execute(path(envp,command_buff),envp);
        
    }
}

