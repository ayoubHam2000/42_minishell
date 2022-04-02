/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:45:05 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/02 18:47:06 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str)
{
	char	*res;
	int		i;
	int		f;

	res = str;
	i = 0;
	f = 0;
	while (*str)
	{
		if ((*str == '\'' || *str == '"') && !f)
			f = *str;
		else if ((*str == '\'' && f == '\'') || (*str == '"' && f == '"'))
			f = 0;
		else
		{
			res[i] = *str;
			i++;
		}
		str++;
	}
	res[i] = 0;
	return (res);
}

int	expand_redt(t_redt *redt)
{
	char	*p;

	if (redt->r_type != RD_DOC)
	{
		p = expansion(redt->file);
		if (!p[0])
		{
			ft_error("minishell: ");
			ft_error(redt->file);
			ft_error(": ambiguous redirect\n");
			return (0);
		}
		p = remove_quotes(p);
		redt->file = p;
	}
	else
		redt->file = remove_quotes(redt->file);
	return (1);
}

void	expand_command(t_cmd *cmd, char *str)
{
	char	*res;

	res = expansion(str);
	if (!res[0])
		cmd->command = NULL;
	else
		cmd->command = remove_quotes(res);
}

void	expand_arg(t_queue *q_args, char *str)
{
	char	*res;

	res = expansion(str);
	while (*res && (*res == ' ' || *res == '\t'))
		res++;
	if ((*res))
		q_enqueue(q_args, remove_quotes(res));
}
