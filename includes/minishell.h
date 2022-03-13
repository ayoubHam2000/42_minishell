/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:34:52 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/13 10:31:15 by aben-ham         ###   ########.fr       */
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
	int		fd[2];
}	t_command;


typedef struct s_env
{
	char	**env;
}	t_env;
//parser
char		*check_sysntax(char *str);
t_queue		*get_structure(char **commands);
char		*add_spaces(char *str);
t_command	**parse_command(char *str);
void		open_files(t_command **cmds);

//expansion
char		*expansion(char *str);
int			expand_redt(t_redt *redt);
void		expand_command(t_cmd *cmd, char *str);
void		expand_arg(t_queue *q_args, char *str);

//open files
int			get_last_doc_index(t_redt **redt);
int			io_flag(int type);
int			get_doc_file(char *delimiter);
void		close_files(t_command **cmds);
void		open_files(t_command **cmds);

//execution: pipe and built in
void		ft_cd(char **cmd);
void		ft_echo(char **cmd);
void		ft_exit(char **cmd);
char		*ft_pwd(void);
char		**ft_export(char **args, char **envp);
char		**ft_unset(char **args, char **envp);

void		execute(t_command	**arrcmd, t_env *env_var);
void		exec_built_in(t_command *command, t_env *env_var);
int			fork_pipes(int n, t_command **arrcmd, t_env *env);
char		*get_cmd_path(char *command, t_env *env);

//other
void		rl_replace_line(const char *text, int i);
int			init_sigaction(void);

void	show(t_command	**commands);



int	ft_isalnum(int c);
int	ft_isalpha(int c);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s1, unsigned int start, size_t len);

int is_valid_identifier(char *str);
char	**ft_split(char const *s, char c);
#endif
