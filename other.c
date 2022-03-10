/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:40:09 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/10 14:40:27 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show(t_command	**commands)
{
	t_command	*c;
	char		**args;
	t_redt		**redt;

	while (1)
	{
		c = *commands;
		if (!c)
			return ;
		args = c->args;
		printf("%s\n", c->command);
		printf("[");
		while (*args)
		{
			printf("%s, ", *args);
			args++;
		}
		printf("]\n");
		redt = c->redt;
		printf("[");
		while (*redt)
		{
			printf("(%s, %d), ", (*redt)->file, (*redt)->r_type);
			redt++;
		}
		printf("]\n");
		commands++;
	}
}
