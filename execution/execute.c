/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:48:32 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/11 22:02:51 by yhakkach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		arr_cmd_len(t_command	**arrcmd)
{
	int	i;

	i = 0;
	while (arrcmd[i])
		i++;
	return (i);
}

void	built_in(t_command *command, t_env *env_var)
{
	int	i;

	if (ft_strcmp(command->command, "cd"))
		ft_cd(command->args);
	else if (ft_strcmp(command->command, "pwd"))
		ft_pwd();
	else if (ft_strcmp(command->command, "echo"))
		ft_echo(command->args);
	else if (ft_strcmp(command->command, "exit"))
		ft_exit(command->args);
	else if (ft_strcmp(command->command, "export"))
		env_var->env = ft_export(command->args, env_var->env);
	else if (ft_strcmp(command->command, "unset"))
		env_var->env = ft_unset(command->args, env_var->env);
}
void	execute(t_command	**arrcmd, t_env *env_var)
{
	int	i;

	//i = fork();
	//if (i == -1)
	//	return ;
	//else if (i == 0)
	//{
		built_in(arrcmd[0], env_var);
		//fork_pipes(arr_cmd_len(arrcmd), arrcmd, env);
	//	exit(0);
	//}
}
