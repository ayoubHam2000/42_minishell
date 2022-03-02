/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 06:04:27 by yhakkach          #+#    #+#             */
/*   Updated: 2022/02/27 17:52:21 by yhakkach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
        return (0);;
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
        return (0);;
    }
            
    return (str);
}

char    **export(char * cmd,char **envp)
{
    char **split;
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