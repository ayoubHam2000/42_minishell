/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:41:44 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/14 00:57:35 by yhakkach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

char	**too(char **envp)
{
	int		i;
	int		j;
	char	**split;
	int		n;

	i = -1;
	j = 0;
	n = ft_arrlen((void **)envp);
	split = malloc(sizeof(char *) * (n  + 1));
	if (!split)
		return (NULL);
	while(envp[++i])
		split[i] = envp[i];
	split[i] = 0;
	return (split);
}

static int	split_test(char c)
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
	if (!f && (c == ' '))
		return (1);
	else if (!f && (c == '>' || c == '<'))
		return (2);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char			*str;
	t_command		**cmds;
	t_env			env_var;

	env_var.env = too(env);
	while(1)
	{
		str = readline(PROMT_STR);
		//str = "ls |ukyu grep";
		if (str)
		{
			if (strlen(str) == 0)
				continue ;
			cmds = parse_command(str);
			if (cmds)
			{
				//show(cmds);
				open_files(cmds);
				execute(cmds, &env_var);
				// wait(NULL);
				close_files(cmds);
				//free_all();
			}
			add_history(str);
		}
		else
			exit(88);
	}
	return (0);
}
