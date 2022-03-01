/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:34:52 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/01 14:48:37 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
//# include <readline/readline.h>
//# include <readline/history.h>
# include <sys/wait.h>

# include "utils.h"

# define PROMT_STR "\e[0;32m➜ \e[0;37mminishell$ \e[0;33m✗ \e[0m"
# define ERR_INTERNAL "Internal Error\n"
# define ERR_MEM "Memory Error\n"
# define ERR_ENV_VAR "Memory Error\n"

typedef struct sigaction	t_sigaction;

//not used yet
typedef struct s_gvar
{
	int	flag;
}	t_gvar;

//sysntax
char	*a_rule(char *str);
char	*b_rule(char *str);
char	*s_rule(char *str);
char	*w_rule(char *str);
char	*t_rule(char *str);
char	*c_rule(char *str);
char	*n_rule(char *str);
char	*check_sysntax(char *str);

void	rl_replace_line(const char *text, int i);
int		init_sigaction(void);
char	*expansion(char *str, char **env);

#endif
