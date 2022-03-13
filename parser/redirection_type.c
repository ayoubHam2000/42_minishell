/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 18:21:49 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/13 18:22:05 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_type(char *token)
{
	size_t	len;

	len = ft_strlen(token);
	if (len == 2 && token[0] == '>' && token[1] == '>')
		return (RD_AP);
	else if (len == 2 && token[0] == '<' && token[1] == '<')
		return (RD_DOC);
	else if (len == 1 && token[0] == '>')
		return (RD_OUT);
	else if (len == 1 && token[0] == '<')
		return (RD_IN);
	else if (len >= 1 && (token[0] == '<' || token[0] == '>'))
		return (RD_ERR);
	return (0);
}
