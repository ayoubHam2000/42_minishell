/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sysntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 18:24:02 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/15 18:12:37 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msk_pipe(char c)
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
	if (!f && (c == '|'))
		return (2);
	return (0);
}

int	msk_tokens(char c)
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
	else if (!f && (c == '>' || c == '<'))
		return (2);
	return (0);
}

int	check_pipe_syntax(char **commands)
{
	size_t	i;
	int		flag;

	if (commands[0] && commands[0][0] == '|')
		return (0);
	i = 0;
	flag = 0;
	while (commands[i])
	{
		if (commands[i][0] == '|' && ft_strlen(commands[i]) != 1)
			return (0);
		else if (flag && commands[i][0] == '|')
			return (0);
		else if (!flag && commands[i][0] == '|')
			flag = 1;
		else
			flag = 0;
		i++;
	}
	if (i >= 2 && commands[i - 1][0] == '|')
		return (0);
	return (1);
}

static int	check_quotes(char *line)
{
	while (*line)
	{
		while (*line && *line != '\'' && *line != '"')
			line++;
		if (*line)
		{
			line++;
			line = ft_strchr(line, *(line - 1));
			if (!line)
				return (0);
			line++;
		}
	}
	return (1);
}

int	check_command_syntax(char **tokens)
{
	size_t	i;
	int		flag;
	int		is_red;

	i = 0;
	flag = 0;
	while (tokens[i])
	{
		if (check_quotes(tokens[i]) == 0)
			return (0);
		is_red = redirection_type(tokens[i]);
		if (is_red == RD_ERR)
			return (0);
		if (is_red && flag)
			return (0);
		else if (is_red && !flag)
			flag = 1;
		else
			flag = 0;
		i++;
	}
	if (flag)
		return (0);
	return (1);
}
