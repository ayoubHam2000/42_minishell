/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:34:52 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/02 20:11:57 by aben-ham         ###   ########.fr       */
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

//token => [file, redirection , pipe, command]

# define CMD_FILE 0
# define CMD_PIPE 1
# define CMD_COMD 2
# define CMD_REDT 3

# define RD_IN 1
# define RD_OUT 2
# define RD_AP 3
# define RD_DOC 4

typedef struct	s_redt
{
	char	r_type;
	char	*file;
}	t_redt ;

typedef struct s_cmd
{
	char	*command;
	t_queue	*q_args;
	t_queue	*q_redt;
}	t_cmd ;

//types
t_cmd	*p_cmd(t_node *node);
t_redt	*p_redt(t_node *node);

//sysntax
char	*a_rule(char *str);
char	*b_rule(char *str);
char	*s_rule(char *str);
char	*w_rule(char *str);
char	*t_rule(char *str);
char	*c_rule(char *str);
char	*n_rule(char *str);
char	*check_sysntax(char *str);

//parser
char	*expansion(char *str);
t_queue	*parse_command(char *str);
t_queue	*get_structur(char *str, char **commands);
char	*add_spaces(char *str);


void	rl_replace_line(const char *text, int i);
int		init_sigaction(void);

#endif
