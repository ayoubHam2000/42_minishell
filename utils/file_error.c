/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 21:29:58 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/12 21:54:00 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_error(char *file_name)
{
	if (!file_name)
		perror("minishell");
	else
		perror(ft_strjoin("minishell: ", file_name));
	return (0);
}
