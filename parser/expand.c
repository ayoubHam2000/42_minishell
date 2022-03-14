/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:45:05 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/13 18:41:31 by yhakkach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str)
{
	if (str[0] == '\'' || str[0] == '"')
		return (ft_substr(str, 1, ft_strlen(str) - 2));
	return (str);
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
		redt->file =p ;
	}
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
