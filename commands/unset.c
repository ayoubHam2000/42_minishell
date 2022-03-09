/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:48:48 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/09 23:41:48 by yhakkach         ###   ########.fr       */
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
///// unset katmse7 variable blanha hewa ani kan7awel n9ezz dak varibale li ghanmse7o mnin kankon kandwzo fe dak use