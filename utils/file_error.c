/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 21:29:58 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/14 18:00:59 by hbourkan         ###   ########.fr       */
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
