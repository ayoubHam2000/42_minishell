/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:17:40 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/01 18:53:18 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fsplit_command(char c)
{
	static int	f;

	if ((c == '\'' || c == '"') && (f == 0 || c == f))
	{
		if (f == 0)
			f = c;
		else
			f = 0;
	}
	if (!f && c == ' ')
		return (1);
	return (0);
}

t_cmd	*create_cmd(char *str, int type)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd *));
}

void	add_to_cmd(t_queue *queue, char **commands)
{
	if (ft_strcmp(*commands, "|"))
		q_enqueue(queue, create_cmd(*commands));
}

t_queue	*get_structur(char *str)
{
	t_queue	*res;
	char	**commands;

	res = q_init();
	commands = ft_fsplit(str, fsplit_command);
	while (*commands)
	{
		add_to_cmd(res, commands);
		commands++;
	}
	free(commands);
	return (res);
}
