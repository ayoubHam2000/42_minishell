/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:22:52 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/05 14:35:21 by aben-ham         ###   ########.fr       */
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
	else if (!c)
		f = 0;
	if (!f && c == '|')
		return (1);
	return (0);
}

static t_command	*get_command(char *c, t_queue *q_arg, t_queue *q_redt)
{
	t_command	*command;
	int			i;

	command = ft_malloc(sizeof(t_command));
	command->command = c;
	command->args = ft_malloc(sizeof(char *) * (q_arg->len + 1));
	command->redt = ft_malloc(sizeof(t_redt *) * (q_redt->len + 1));
	i = -1;
	while (1)
	{
		command->args[++i] = q_dequeue(q_arg);
		if (!command->args[i])
			break ;
	}
	i = -1;
	while (1)
	{
		command->redt[++i] = q_dequeue(q_redt);
		if (!command->redt[i])
			break ;
	}
	return (command);
}

static t_queue	*get_commands(t_queue *s)
{
	t_queue		*res;
	t_cmd		*c;
	t_command	*cmd;

	res = q_init();
	while (1)
	{
		c = q_dequeue(s);
		if (!c)
			break ;
		cmd = get_command(c->command, c->q_args, c->q_redt);
		q_enqueue(res, cmd);
	}
	return (res);
}

t_queue	*parse_command(char *str)
{
	t_queue	*res;
	char	**commands;

	res = NULL;
	if (check_sysntax(str))
	{
		commands = ft_fsplit(str, fsplit_command);
		res = get_structure(commands);
		if (!res)
			return (NULL);
		res = get_commands(res);
	}
	else
	{
		ft_error("Not Valide Sysntax\n");
	}
	return (res);
}
