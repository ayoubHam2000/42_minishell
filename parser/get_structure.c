/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_structure.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 15:17:40 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/04 18:21:56 by aben-ham         ###   ########.fr       */
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

static void	add_redt(t_queue *queue, char **tokens)
{
	t_redt	*redt;
	size_t	len;
	size_t	i;

	redt = ft_malloc(sizeof(t_redt));
	redt->r_type = is_redirection(*tokens);
	len = ft_strlen(*tokens);
	i = 0;
	if (len == 1 || (len == 2 && (*tokens[0] == '>' || *tokens[0] == '<') && (*tokens[1] == '<' || *tokens[1] == '>')))
		redt->file = ft_strdup(*(tokens + 1));
	else
	{
		while ((*tokens)[i] == '>' || (*tokens)[i] == '<')
			i++;
		redt->file = ft_substr(*tokens, i, len - i);
	}
	q_enqueue(queue, redt);
}

static t_cmd	*get_command(char **tokens)
{
	t_cmd	*cmd;

	cmd = ft_malloc(sizeof(t_cmd));
	cmd->q_args = q_init();
	cmd->q_redt = q_init();
	cmd->command = NULL;
	while (*tokens)
	{
		if (is_redirection(*tokens))
		{
			add_redt(cmd->q_redt, tokens);
			if (!expand_redt(cmd->q_redt->first->p))
			{
				free_cmd(cmd);
				return (NULL);
			}
			if (ft_strlen(*tokens) <= 2)
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

t_queue	*get_structure(char **commands)
{
	t_queue	*q_cmd;
	char	**tokens;
	t_cmd	*cmd;

	q_cmd = q_init();
	while (*commands)
	{
		tokens = ft_fsplit(*commands, fsplit_command);
		cmd = get_command(tokens);
		if (!cmd)
		{
			free_arr_str(tokens);
			q_clear(q_cmd, free_cmd);
			free(q_cmd);
			return (NULL);
		}
		free_arr_str(tokens);
		q_enqueue(q_cmd, cmd);
		commands++;
	}
	return (q_cmd);
}
