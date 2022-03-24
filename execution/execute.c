/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:48:32 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/24 11:07:02 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# include <errno.h>



static char	**add_arg_0(char **args, char *arg0)
{
	char	**res;
	int		i;

	i = 0;
	while (args[i])
		i++;
	res = ft_malloc(sizeof(char *) * (i + 2));
	i = 0;
	res[i] = arg0;
	while (args[i])
	{
		res[i + 1] = args[i];
		i++;
	}
	res[i + 1] = NULL;
	return (res);
}

static int	is_builtin(char *str)
{
	const char	*built_in[] = {"cd", "pwd", "echo", "exit", "export", "unset","env", NULL};
	int			i;

	i = 0;
	while (built_in[i])
	{
		if (str && ft_strcmp(str, (char *)built_in[i]))
			return (1);
		i++;
	}
	return (0);
}

static char	*env_cmd_path(char *cmd)
{
	char	*path;
	char	**pathsplit;
	int		i;
	char	*str;
	char	**envp;

	i = 0;
	envp = env_var(NULL);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!envp[i])
		return (NULL);
	path = envp[i] + 5;
	pathsplit = ft_split(path, ':');
	i = 0;
	while (pathsplit[i])
	{
		str = ft_strjoin(pathsplit[i++], "/");
		str = ft_strjoin(str, cmd);
		if (access(str, X_OK | F_OK) == 0)
			return (str);			
	}
		printf(" %s: command not found \n",cmd);
			exit(127);
	return (NULL);
}

char	*get_cmd_path(char *command)
{
	if (*command == '/')
		return (command);
	else if (ft_strchr(command, '/'))
	{
		command = ft_strjoin("/", command);
		return (ft_strjoin(get_path(), command));
	}
	else
		return (env_cmd_path(command));
}

int	exec_built_in(t_command *command)
{
	int	i;

	i = 0;
	if (ft_strcmp(command->command, "cd"))
		i = ft_cd(command->args);
	else if (ft_strcmp(command->command, "pwd"))
		i = ft_pwd();
	else if (ft_strcmp(command->command, "echo"))
		i = ft_echo(command->args);
	else if (ft_strcmp(command->command, "exit"))
		ft_exit(command->args);
	else if (ft_strcmp(command->command, "export"))
		i = ft_export(command->args);
	else if (ft_strcmp(command->command, "unset"))
		i = ft_unset(command->args);
	else if (ft_strcmp(command->command, "env"))
 		i = ft_env();
	return (0);
 }

void	exec_cmd(t_command *cmd)
{
	char	*path;
	char	**args;

	if (cmd->command == NULL)
		return ;
	else if (is_builtin(cmd->command))
	{
		exec_built_in(cmd);
		exit(13);
	}
	else
	{
		path = get_cmd_path(cmd->command);
		if (!path)
			return ;
		args = add_arg_0(cmd->args, path);
		execve(args[0], args, env_var(NULL));
	}
}

///////

static int	spawn_proc(int in, int out, t_command *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (in != 0)
		{
			dup2(in, 0);
			// close(in);
		}
		if (out != 1)
		{
			dup2(out, 1);
			// close(out);
		}
		exec_cmd(cmd);
	}
	// close(out);
	// close(in);
	
	return (pid);
}

int    fork_pipes(int n, t_command **arrcmd)
{
    int        i;
    int        in;
    int        *fd;

	int			redin;
	int			redout;

    i = 0;	

    int filein = arrcmd[0]->fd[0];
	int fileout = arrcmd[0]->fd[1];
	
    while (i < n - 1)
    {
        int fd[2];

		 filein = arrcmd[i]->fd[0];
		 fileout = arrcmd[i]->fd[1];
        pipe(fd);
		 if (fileout != 1)
		 {
	 		redout = fileout;
		 	close(fd[1]);
			 fd[1] = redout;
		 }
		 // we  have file
		if (filein != 0)
			 redin =  filein;
        spawn_proc(redin, fd[1], arrcmd[i]);
        close(fd[1]);		 	
        redin = fd[0];
        i++;
    }

	filein = arrcmd[i]->fd[0];
	fileout = arrcmd[i]->fd[1];
	if(filein != 0)
	{
		redin = filein;
	}

	int pid = fork();
	if (pid == 0)
	{	
		if (redin != 0)
		{
			dup2(redin, 0);
		}
		if (fileout != 1)
		{
			dup2(fileout, 1);
		}
		exec_cmd(arrcmd[i]);
		exit(0);
	}
	return (pid);
}

int	execute(t_command	**arrcmd)
{
	int	i;
	int status;
	int	last_pid;
	int	ret;

	if (is_builtin(arrcmd[0]->command) && ft_arrlen((void **)arrcmd) == 1)
	{
		ret = exec_built_in(arrcmd[0]);
		set_exit_status(ret);
		return (ret);
	}
	else
	{
		last_pid = fork_pipes(ft_arrlen((void **)arrcmd), arrcmd);
		ret = waitpid(-1, &status, 0);
		while (ret != 0 && ret != -1)
		{
			if (ret == last_pid)
				set_exit_status(status);
			ret = waitpid(-1, &status, 0);
		}
		return (ret);
	}
}
