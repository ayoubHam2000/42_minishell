/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:41:44 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/15 23:48:14 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**too(char **envp)
{
	int		i;
	int		j;
	char	**split;
	int		n;

	i = -1;
	j = 0;
	n = ft_arrlen((void **)envp);
	split = ft_malloc(sizeof(char *) * (n  + 1));
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

char	*ft_readline(int s);

int	main(int ac, char **av, char **env)
{
	char			*str;
	t_command		**cmds;
	t_env			env_var;

	env_var.env = too(env);
	init_sigaction();
	while(1)
	{
		str = readline(PROMT_STR);
		if (str)
		{
			if (strlen(str) == 0)
				continue ;
			cmds = parse_command(str);
			if (cmds)
			{
				ft_readline(1);
				open_files(cmds);
				show(cmds);
				execute(cmds, &env_var);
				close_files(cmds);
				free_all();
				ft_readline(0);
			}
			add_history(str);
		}
		else
			exit(0);
	}
	return (0);
}
