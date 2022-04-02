/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 21:27:08 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/02 20:24:58 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_output_file(int *fd, t_redt *redt)
{
	if (fd[1] != -1)
	{
		close(fd[1]);
		fd[1] = -1;
	}
	fd[1] = open(redt->file, io_flag(redt->r_type), 0666);
	if (fd[1] == -1)
		return (file_error(redt->file));
	return (1);
}

static int	open_input_file(int *fd, t_redt *redt, int flag)
{
	int	tmp_fd;

	if (!flag)
	{
		tmp_fd = open(redt->file, io_flag(redt->r_type));
		if (tmp_fd == -1)
			return (file_error(redt->file));
	}
	else
	{
		if (fd[0] != -1)
		{
			close(fd[0]);
			fd[0] = -1;
		}
		fd[0] = open(redt->file, io_flag(redt->r_type));
		if (fd[0] == -1)
			return (file_error(redt->file));
	}
	return (1);
}

static int	open_io_file_for_cmd(t_command *cmd, t_redt **redt)
{
	int	r;
	int	last_doc;

	last_doc = get_last_doc_index(redt);
	r = 0;
	while (redt[r])
	{
		if (redt[r]->r_type == RD_OUT || redt[r]->r_type == RD_AP)
		{
			if (!open_output_file(cmd->fd, redt[r]))
				return (0);
		}
		if (redt[r]->r_type == RD_IN)
		{
			if (!open_input_file(cmd->fd, redt[r], r > last_doc))
				return (0);
		}
		r++;
	}
	return (1);
}

static int	open_doc_file_for_cmd(t_command *cmd, t_redt **redt)
{
	int	r;

	r = 0;
	while (redt[r])
	{
		if (redt[r]->r_type == RD_DOC)
		{
			if (cmd->fd[0] != -1)
				close(cmd->fd[0]);
			cmd->fd[0] = get_doc_file(redt[r]->file, redt[r]->with_quote);
			if (cmd->fd[0] == -1)
				return (file_error("Heredoc"));
			else if (cmd->fd[0] == -2)
			{
				cmd->fd[0] = -1;
				return (0);
			}
		}
		r++;
	}
	return (1);
}

int	open_files(t_command **cmds)
{
	int	r;

	r = 0;
	while (cmds[r])
	{
		if (!open_doc_file_for_cmd(cmds[r], cmds[r]->redt))
			return (0);
		r++;
	}
	r = 0;
	while (cmds[r])
	{
		if (!open_io_file_for_cmd(cmds[r], cmds[r]->redt))
			cmds[r]->command = NULL;
		if (cmds[r]->fd[0] == -1)
			cmds[r]->fd[0] = 0;
		if (cmds[r]->fd[1] == -1)
			cmds[r]->fd[1] = 1;
		r++;
	}
	return (1);
}
