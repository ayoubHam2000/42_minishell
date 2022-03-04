/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:44:22 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/04 20:31:22 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr_str(char **str)
{
	char	**tmp;

	tmp = str;
	while (*tmp)
	{
		//free(*tmp);
		tmp++;
	}
	//free(*tmp);
	//free(str);
}

void	p_free_redt(void *p)
{
	//free(((t_redt *)p)->file);
	//free(p);
}

void	free_cmd(void *p)
{
	t_cmd	*cmd;

	cmd = p;
	if (cmd->command)
		//free(cmd->command);
	q_clear(cmd->q_args, NULL);
	q_clear(cmd->q_redt, p_free_redt);
	//free(cmd->q_args);
	//free(cmd->q_redt);
	//free(cmd);
}
