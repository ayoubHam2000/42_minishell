/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:08:47 by hbourkan          #+#    #+#             */
/*   Updated: 2022/04/15 01:19:20 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args)
{
	char	*path;

	if (!args[0])
		path = ft_getenv("HOME");
	else if (ft_strcmp(args[0], "~"))
		path = ft_getenv("HOME");
	else if (ft_strcmp(args[0], "-"))
	{
		path = ft_getenv("OLDPWD");
		printf("%s\n", path);
	}
	else
		path = ft_strdup(args[0]);
	if (chdir(path) == -1)
	{
		perror("Directory not found");
		return (1);
	}
	return (0);
}
