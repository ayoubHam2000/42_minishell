/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:14:58 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/10 15:33:22 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **args)
{
	char	*path;

	if (args[2] && args[1])
	{
		ft_error("cd: too many arguments\n");
		return ;
	}
	else if (!args[1])
		path = getenv("HOME");
	else
		path = args[1];
	if (path && path[0] == '~')
		path = getenv("HOME");
	if (path && path[0] == '-' && !path[1])
	{
		path = getenv("OLDPWD");
		printf("%s\n", path);
	}
	else if (chdir(path) < 0)
		printf("cd: chdir error: %s\n", path);
	else
		ft_pwd();
}
