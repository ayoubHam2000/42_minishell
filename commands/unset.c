/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:48:48 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/09 10:03:50 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char   ** unset(char *cmd,char   **envp)
{
        int     i;
        int     j;
        char    **split;
        char    **unse;
                
        i = 0;
        j = 0;
        
        split = ft_split(cmd,' ');

        unse = malloc(sizeof(char *) * ft_arraylen(envp) - 1 ); 
        while(envp[i])
        {
            if (!strncmp(envp[i],split[1],ft_strlen(split[1])))
                    i++;
            unse[j++] = envp[i++];
        }
        
        unse[j]= 0;
        
    return (unse);    
}
