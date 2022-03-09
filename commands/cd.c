/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:14:58 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/09 10:15:55 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"



void  pwd()
{
    char    cwd[1024];
    getcwd(cwd,sizeof(cwd));
    printf("%s",cwd);
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
		
	if (path && path[0] == '-' && !path[1])
	{
		path = getenv("OLDPWD");
		printf("%s\n", path);
	}
	if (chdir(path) < 0)
	{
		printf("cd: chdir error: %s\n", path);
		return ;
	}else
    {
        pwd();
    }
}

int    main(int argc ,char **argv)
{
      cd(argv);
}