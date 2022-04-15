/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 18:34:52 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/15 23:08:04 by hbourkan         ###   ########.fr       */
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
# include <termios.h>

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
# define STDIN 0
# define STDOUT 1

typedef struct s_redt
{
	char	r_type;
	char	*file;
	int		with_quote;
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

typedef struct s_status
{
	int	status;
	int	last_status;
	int	res;
}	t_status;

//parser
t_queue		*get_structure(t_queue *cmds);
t_command	**parse_command(char *str);

//parser->synatx
int			msk_pipe(char c);
int			msk_tokens(char c);
int			check_pipe_syntax(char **commands);
int			check_command_syntax(char **tokens);

//parser->open files
int			get_last_doc_index(t_redt **redt);
int			io_flag(int type);
int			get_doc_file(char *delimiter, int with_quote);
void		close_files(t_command **cmds);
int			open_files(t_command **cmds);

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

//execution->built in
char		*get_path(void);
int			ft_cd(char **args);
int			ft_echo(char **args, int fd);
int			ft_exit(char **args, int fd);
int			ft_pwd(int fd);
int			ft_export(char **args, int fd);
int			ft_unset(char **args, int fd);
int			ft_env(char **args, int type, int fd);

//execution->pipe and execute
// int			fork_pipes(int n, t_command **arrcmd);
// int			exec_built_in(t_command *command);
// int			execute(t_command	**arrcmd);

//execution->utils
void		execute(t_command **cmds);
void		in_out_red(int input, int output);
void		in_out_red(int input, int output);
void		redirec(t_command **cmds, int **pipefd, int i, int j);
void		open_pipes(int nb_pipes, int **pipefd);
void		close_pipes(int nb_pipes, int **pipefd);
int			execute_builtin(t_command **cmds, int i);
int			counter(char **arr);
int			equal_position(char *str);
int			compare_env(char *s1, char *s2);
char		*ft_strjoin_path(char const *s1, char const *s2);
char		*getpath(char *cmd);
char		**join_args(t_command **cmds, int index);
int			get_cmds_nb(char **args);
int			is_builtin(char *cmd);
int			ft_validvarname(int c, int c2);
int			check_vn(char *arg);
void		get_overcmd(t_command **cmds, int *childpid);
void		cmd_type(t_command **cmds, int j, int nb_pipes, int **pipefd);
void		executer(t_command **cmds, int j, int nb_pipes, int **pipefd);
void		executer2(t_command **cmds, int j);

int			du_exit_status(int exit_status, int force);
void		set_exit_status(int exit_status);
int			get_exit_status(void);

//other
void		rl_replace_line(const char *text, int i);
int			init_sigaction(void);
int			du_working(int affect);

#endif
