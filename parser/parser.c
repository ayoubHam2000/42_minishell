/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:22:52 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/01 14:48:40 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_command(char *str, char **env)
{
	char	*res;

	res = expansion(str, env);
	str = check_sysntax(res);
	if (!str)
		printf("Syntax Error\n");
	else
		printf("%s\n", res);
	free(res);
	return (0);
}
