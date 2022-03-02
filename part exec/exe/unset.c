/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:48:48 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/01 18:50:10 by yhakkach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char   ** unset(char *cmd,char   **envp)
{
        int     i;
        int     j;
        char    **split;
        char    **unse;
                
        i = 0;
        j = 0;
        
        split = ft_split(cmd,' ');

       //// verf
        unse = malloc(sizeof(char *) * ft_arraylen(envp) - 1 ); 
        while(envp[i])
        {
            if (!strncmp(envp[i],split[1],4))
                    i++;
            unse[j++] = envp[i++];
        }
        
        unse[j]= 0;
    return (unse);    
}