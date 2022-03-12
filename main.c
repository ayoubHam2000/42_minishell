/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:41:44 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/12 21:57:09 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

int	ft_arraylen(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
	{
		i++;
	}
	return (i);
}

char        **too(char **envp)

{
    
    int     i;
    int     j;
    char    **split;
    int     n;
    i = -1;
    j = 0;

    n = ft_arraylen(envp);
    split = malloc(sizeof(char *) * (n  + 1));
    if (!split)
        return (NULL);
    while(envp[++i])
        split[i] = envp[i];
    split[i] = 0;
    return (split);
}
int	main(int ac, char **av, char **env)
{
	char			*str;
	int				status;
	t_command		**cmds;
	t_env			env_var;

	env_var.env = too(env);
	while(1){
		str = readline(PROMT_STR);
		if (str)
		{
			if (strlen(str) == 0)
				continue ;
			cmds = parse_command(str);
			if (cmds)
			{
				//show(cmds);
				open_files(cmds);
				//execute(cmds, &env_var);
				//wait(NULL);
				close_files(cmds);
				//free_all();
			}
			add_history(str);
		}
		else
			exit(0);
	}
	return (0);
}
