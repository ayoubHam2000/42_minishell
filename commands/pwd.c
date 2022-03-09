/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:10:45 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/09 23:40:47 by yhakkach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void  pwd()
{
    char    cwd[1024];
    getcwd(cwd,sizeof(cwd));
    printf("%s",cwd);
}
////// hadi dyal lpaths wakha rakha khedama dyal path