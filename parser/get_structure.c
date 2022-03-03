/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_structure.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:17:40 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/03 14:19:43 by aben-ham         ###   ########.fr       */
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
	if (!f && c == ' ')
		return (1);
	return (0);
}

static int	is_redirection(char *str)
{
	if (str[0] == '>' && str[1] == '>')
		return (RD_AP);
	else if (str[0] == '<' && str[1] == '<')
		return (RD_DOC);
	else if (str[0] == '>')
		return (RD_OUT);
	else if (str[0] == '<')
		return (RD_IN);
	return (0);
}

static t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_malloc(sizeof(t_cmd));
	cmd->q_args = q_init();
	cmd->q_redt = q_init();
	cmd->command = NULL;
	return (cmd);
}

static t_cmd	*get_command(char **tokens)
{
	t_cmd	*cmd;
	t_redt	*redt;

	cmd = init_cmd();
	while (*tokens)
	{
		if (is_redirection(*tokens))
		{
			redt = ft_malloc(sizeof(t_redt));
			redt->r_type = is_redirection(*tokens);
			redt->file = *(tokens + 1);
			free(*tokens);
			q_enqueue(cmd->q_redt, redt);
			tokens++;
		}
		else if (!cmd->command)
			cmd->command = *tokens;
		else
			q_enqueue(cmd->q_args, *tokens);
		tokens++;
	}	
	return (cmd);
}

t_queue	*get_structur(char **commands)
{
	t_queue	*q_cmd;
	char	**tokens;

	q_cmd = q_init();
	while (*commands)
	{
		tokens = ft_fsplit(*commands, fsplit_command);
		q_enqueue(q_cmd, get_command(tokens));
		free(*commands);
		free(tokens);
		commands++;
	}
	return (q_cmd);
}
