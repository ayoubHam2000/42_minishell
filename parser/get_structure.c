/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_structure.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:17:40 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/02 18:41:19 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_malloc(sizeof(t_cmd));
	cmd->q_args = q_init();
	cmd->q_redt = q_init();
	cmd->command = NULL;
	return (cmd);
}

static t_redt	*get_redt(char *r, char *file)
{
	t_redt	*redt;

	redt = ft_malloc(sizeof(t_redt));
	redt->r_type = redirection_type(r);
	redt->file = file;
	redt->with_quote = 0;
	if (ft_strchr(file, '\'') || ft_strchr(file, '"'))
		redt->with_quote = 1;
	return (redt);
}

static t_cmd	*get_command(char **tokens)
{
	t_cmd	*cmd;
	t_redt	*redt;

	cmd = new_cmd();
	while (*tokens)
	{
		if (redirection_type(*tokens))
		{
			redt = get_redt(*tokens, *(tokens + 1));
			if (!expand_redt(redt))
				return (NULL);
			q_enqueue(cmd->q_redt, redt);
			tokens++;
		}
		else if (!cmd->command)
			expand_command(cmd, *tokens);
		else
			expand_arg(cmd->q_args, *tokens);
		tokens++;
	}
	return (cmd);
}

t_queue	*get_structure(t_queue *cmds)
{
	t_queue	*res;
	t_node	*node;
	t_cmd	*cmd;
	char	**tokens;

	node = cmds->first;
	res = q_init();
	while (node)
	{
		tokens = node->p;
		cmd = get_command(tokens);
		if (!cmd)
			return (NULL);
		q_enqueue(res, cmd);
		node = node->next;
	}
	return (res);
}
