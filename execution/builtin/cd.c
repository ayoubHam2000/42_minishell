/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:14:58 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/25 16:39:24 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args)
{
	char	*path;

	if (!args[0])
		path = getenv("HOME");
	else
		path = args[0];
	if (path && path[0] == '~')
		path = getenv("HOME");
	if (path && path[0] == '-' && !path[1])
	{
		path = getenv("OLDPWD");
	}
	else if (chdir(path) < 0)
	{
		ft_error("cd: chdir error: ");
		ft_error(path);
		ft_error("\n");
		return (1);
	}
	return (0);
}
