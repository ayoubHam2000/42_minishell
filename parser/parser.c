/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:22:52 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/24 11:09:05 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_queue	*get_commands_tokens(char **commands)
{
	size_t	i;
	t_queue	*q;
	char	**tokens;

	q = q_init();
	i = 0;
	while (commands[i])
	{
		if (commands[i][0] == '|')
		{
			i++;
			continue ;
		}
		tokens = msk_split(commands[i], msk_tokens);
		if (check_command_syntax(tokens))
			q_enqueue(q, tokens);
		else
			return (NULL);
		i++;
	}
	return (q);
}

static t_command	*get_command(char *c, t_queue *q_arg, t_queue *q_redt)
{
	t_command	*command;
	int			i;

	command = ft_malloc(sizeof(t_command));
	command->command = c;
	command->fd[0] = -1;
	command->fd[1] = -1;
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

static t_command	**get_commands(t_queue *s)
{
	t_command	**res;
	t_cmd		*c;
	t_command	*cmd;
	int			i;

	i = 0;
	res = ft_malloc(sizeof(t_command *) * (s->len + 1));
	while (1)
	{
		c = q_dequeue(s);
		if (!c)
			break ;
		cmd = get_command(c->command, c->q_args, c->q_redt);
		res[i] = cmd;
		i++;
	}
	res[i] = NULL;
	return (res);
}

t_command	**parse_command(char *str)
{
	char	**commands;
	t_queue	*q;

	commands = msk_split(str, msk_pipe);
	if (check_pipe_syntax(commands))
	{
		q = get_commands_tokens(commands);
		if (q)
		{
			q = get_structure(q);
			if (!q)
				return (NULL);
			return (get_commands(q));
		}
	}
	ft_error(ERR_SYNATX_ERROR);
	return (NULL);
}
