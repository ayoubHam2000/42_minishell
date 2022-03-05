/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:34:52 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/05 14:24:31 by aben-ham         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# include "utils.h"

# define PROMT_STR "\e[0;32m➜ \e[0;37mminishell$ \e[0;33m✗ \e[0m"
# define ERR_INTERNAL "Internal Error\n"
# define ERR_ENV_VAR "Memory Error\n"

typedef struct sigaction	t_sigaction;

# define RD_IN 1
# define RD_OUT 2
# define RD_AP 3
# define RD_DOC 4

typedef struct s_redt
{
	char	r_type;
	char	*file;
}	t_redt;

typedef struct s_cmd
{
	char	*command;
	t_queue	*q_args;
	t_queue	*q_redt;
}	t_cmd;

typedef struct s_command
{
	char	*command;
	char	**args;
	t_redt	**redt;
}	t_command;

//parser
char	*check_sysntax(char *str);
t_queue	*parse_command(char *str);
t_queue	*get_structure(char **commands);
char	*add_spaces(char *str);
//expansion
char	*expansion(char *str);
int		expand_redt(t_redt *redt);
void	expand_command(t_cmd *cmd, char *str);
void	expand_arg(t_queue *q_args, char *str);

//other
void	rl_replace_line(const char *text, int i);
int		init_sigaction(void);

#endif
