/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:45:05 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/04 20:31:56 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		expand_redt(t_redt *redt)
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
			//free(p);
			return (0);
		}
		//free(redt->file);
		redt->file = p;	
	}
	return (1);
}

void	expand_command(t_cmd *cmd, char *str)
{
	char	*res;

	res = expansion(str);
	if (!res[0])
	{
		//free(res);
		cmd->command = NULL;
	}
	else
		cmd->command = res;
}

void	expand_arg(t_queue *q_args, char *str)
{
	char	*res;
	char	*tmp;

	res = expansion(str);
	tmp = res;
	while (*tmp && (*tmp == ' ' || *tmp == '\t'))
		tmp++;
	if ((*tmp))
		//free(res);
	//else
	{
		if (res[0] == '\'' || res[0] == '"')
		{
			tmp = res;
			res = ft_substr(res, 1, ft_strlen(res) - 2);
			//free(tmp);
		}
		q_enqueue(q_args, res);
	}
}
