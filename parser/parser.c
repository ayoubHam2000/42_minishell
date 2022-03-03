/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:22:52 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/03 14:32:16 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		free(c->q_args);
		free(c->q_redt);
		free(c);
	}
	free(s);
	return (res);
}

t_queue	*parse_command(char *str)
{
	t_queue	*res;
	char	**commands;
	char	*format_str;

	if (check_sysntax(str))
	{
		str = add_spaces(str);
		format_str = expansion(str);
		commands = ft_split(format_str, '|');
		res = get_structur(commands);
		res = get_commands(res);
		free(str);
		free(format_str);
		free(commands);
	}
	else
	{
		ft_putstr("Not Valide Sysntax\n");
	}
	return (res);
}
