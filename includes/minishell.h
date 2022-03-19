/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhakkach <yhakkach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:34:52 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/19 17:00:14 by yhakkach         ###   ########.fr       */
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
# include <errno.h>

# include "utils.h"

# define PROMT_STR "\e[0;32m➜ \e[0;37mminishell$ \e[0;33m✗ \e[0m"
# define ERR_INTERNAL "Internal Error\n"
# define ERR_ENV_VAR "Memory Error\n"
# define ERR_SYNATX_ERROR "Synatx Error\n"

# define RD_ERR -1
# define RD_IN 1
# define RD_OUT 2
# define RD_AP 3
# define RD_DOC 4
# define RD_DOC_READ 5

int	g_sig;

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
	t_redt	**redt; // pipe
	int		fd[2];// pipe
}	t_command;


typedef struct s_env
{
	char	**env;
}	t_env;

//parser
t_queue		*get_structure(t_queue *cmds);
t_command	**parse_command(char *str);

//parser->synatx
int			msk_pipe(char c);
int 		msk_tokens(char c);
int			check_pipe_syntax(char **commands);
int			check_command_syntax(char **tokens);

//parser->open files
int			get_last_doc_index(t_redt **redt);
int			io_flag(int type);
int			get_doc_file(char *delimiter);
void		close_files(t_command **cmds);
void		open_files(t_command **cmds);

//parser->expansion
char		*expansion(char *str);
int			expand_redt(t_redt *redt);
void		expand_command(t_cmd *cmd, char *str);
void		expand_arg(t_queue *q_args, char *str);
char		*ft_getenv(char *var);
char		**env_var(char **new_env);
char		**get_copy_env(char **env);

//parsing->utils
int			redirection_type(char *token);

//=======
//=======
//=======

//execution: pipe and built in
char		*get_path(void);
int			ft_cd(char **cmd);
int			ft_echo(char **cmd);
void		ft_exit(char **cmd);
int			ft_pwd(void);
int			ft_export(char **args);
int			ft_unset(char **args);

int			execute(t_command	**arrcmd);
int			exec_built_in(t_command *command);
int			fork_pipes(int n, t_command **arrcmd);
char		*get_cmd_path(char *command);
int			ft_env(void);


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
void 	printarray(char **array, int k);

#endif
