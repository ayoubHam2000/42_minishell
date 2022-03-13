/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:48:32 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/13 16:01:59 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	const char	*built_in[] = {"cd", "pwd", "echo", "exit", "export", "unset", NULL};
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

static char	*env_cmd_path(char *cmd, char **envp)
{
	char	*path;
	char	**pathsplit;
	int		i;
	char	*str;

	i = 0;
	while (envp[i])
	{
		if (!strncmp(envp[i], "PATH=", 5))
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
	return (NULL);
}

char	*get_cmd_path(char *command, t_env *env)
{
	if (*command == '/')
		return (command);
	else if (ft_strchr(command, '/'))
	{
		command = ft_strjoin("/", command);
		return (ft_strjoin(ft_pwd(), command));
	}
	else
		return (env_cmd_path(command, env->env));
}

void	exec_built_in(t_command *command, t_env *env)
{
	if (ft_strcmp(command->command, "cd"))
		ft_cd(command->args);
	else if (ft_strcmp(command->command, "pwd"))
		ft_pwd();
	else if (ft_strcmp(command->command, "echo"))
		ft_echo(command->args);
	else if (ft_strcmp(command->command, "exit"))
		ft_exit(command->args);
	else if (ft_strcmp(command->command, "export"))
		env->env = ft_export(command->args, env->env);
	else if (ft_strcmp(command->command, "unset"))
		env->env = ft_unset(command->args, env->env);
}

void	exec_cmd(t_command *cmd, t_env *env)
{
	char	*path;
	char	**args;

	if (cmd->command == NULL)
		return ;
	else if (is_builtin(cmd->command))
	{
		exec_built_in(cmd, env);
		exit(0);
	}
	else
	{
		path = env_cmd_path(cmd->command, env->env);
		if (!path)
			return ;
		args = add_arg_0(cmd->args, path);
		execve(args[0], args, env->env);
	}
}

///////

static int	spawn_proc(int in, int out, t_command *cmd, t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		exec_cmd(cmd, env);
	}
	return (pid);
}

int	fork_pipes(int n, t_command **arrcmd, t_env *env)
{
	int		i;
	int		in;
	int		*fd;

	i = 0;
	in = 0;
	while (i < n - 1)
	{
		fd = arrcmd[i]->fd;
		printf("%d, %d\n", fd[0], fd[1]);
		pipe(fd);
		spawn_proc(in, fd[1], arrcmd[i], env);
		close(fd[1]);
		in = fd[0];
		i++;
	}
	if (in != 0)
		dup2(in, 0);
	exec_cmd(arrcmd[i], env);
	return (0);
}

//////

void	execute(t_command	**arrcmd, t_env *env_var)
{
	int	i;

	if (is_builtin(arrcmd[0]->command) && ft_arrlen((void **)arrcmd) == 1)
	{
		exec_built_in(arrcmd[0], env_var);
	}
	else
	{
		i = fork();
		if (i == -1)
			return ;
		else if (i == 0)
		{
			fork_pipes(ft_arrlen((void **)arrcmd), arrcmd, env_var);
			exit(0);
		}
	}
}
