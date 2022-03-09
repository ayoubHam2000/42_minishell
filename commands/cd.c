/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:14:58 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/09 23:33:17 by yhakkach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// typedef struct s_command
// {
// 	char	*command;
// 	char	**args;
// 	t_redt	**redt;
// }	t_command;


void	cd(char **cmd)
{
	char	*path;
	
	if (cmd[2] && cmd[1]) // ila kano f09 2 dyal arg kheso ykherj
	{
		printf("cd: too many arguments\n");
		return ;
	}
	if (!cmd[1])
		path = getenv("HOME");  // ila mkantch cd ghadymchi home nichan
	else
		path = cmd[1];
	if (path && path[0] == '~') // cd ~ katdina home nichan
		path = getenv("HOME"); //change
		
	if (path && path[0] == '-' && !path[1]) // cd - old path
	{
		path = getenv("OLDPWD");
		printf("%s\n", path);
	}
	if (chdir(path) < 0) ///  hena fe function chdir  katkmchi l ay path 3titiha
	{
		printf("cd: chdir error: %s\n", path);
		return ;
	}
}

int    main(int argc ,char **argv)
{
      cd(argv);
}