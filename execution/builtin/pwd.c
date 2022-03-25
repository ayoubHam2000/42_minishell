/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:10:45 by yhakkach          #+#    #+#             */
/*   Updated: 2022/03/25 16:54:51 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(void)
{
	const int	size = 1024;
	char		*cwd;

	cwd = ft_malloc(size);
	getcwd(cwd, size);
	return (cwd);
}

int	ft_pwd(void)
{
	char	*res;

	res = get_path();
	if (!res)
		return (1);
	ft_print_out(res);
	ft_print_out("\n");
	return (0);
}
