/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:17:40 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/02 20:21:44 by aben-ham         ###   ########.fr       */
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

int	is_redirection(char *str)
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

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->q_args = q_init();
	cmd->q_redt = q_init();
	cmd->command = NULL;
	return (cmd);
}

t_cmd	*get_command(char *str)
{
	char	**tokens;
	t_cmd	*cmd;
	t_redt	*redt;

	tokens = ft_fsplit(str, fsplit_command);
	cmd = init_cmd();
	while (*tokens)
	{
		if (is_redirection(*tokens))
		{
			redt = malloc(sizeof(t_redt));
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

t_queue	*get_structur(char *str, char **commands)
{
	t_queue	*q_cmd;
	char	*tmp;

	q_cmd = q_init();
	while (*commands)
	{
		q_enqueue(q_cmd, get_command(*commands));
		free(*commands);
		commands++;
	}
	return (q_cmd);
}
