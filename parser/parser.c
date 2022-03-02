/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:22:52 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/02 20:09:19 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_queue	*parse_command(char *str)
{
	t_queue	*res;
	char	**commands;
	char	*format_str;

	if (check_sysntax(str))
	{
		format_str = add_spaces(str);
		format_str = expansion(str);
		commands = ft_split(str, '|');
		res = get_structur(format_str, commands);
		free(format_str);
	}
	return (res);
}
