/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 21:27:12 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/24 10:05:14 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_last_doc_index(t_redt **redt)
{
	int	r;
	int	last_doc_index;

	r = 0;
	last_doc_index = -1;
	while (redt[r])
	{
		if (redt[r]->r_type == RD_DOC)
			last_doc_index = r;
		r++;
	}
	return (last_doc_index);
}

int	io_flag(int type)
{
	if (type == RD_OUT || type == RD_DOC)
		return (O_CREAT | O_WRONLY | O_TRUNC);
	else if (type == RD_AP)
		return (O_CREAT | O_WRONLY | O_APPEND | O_TRUNC);
	else if (type == RD_IN || type == RD_DOC_READ)
		return (O_RDONLY);
	return (0);
}

int	get_doc_file(char *delimiter)
{
	static unsigned short	index;
	int						fd;
	char					*path;
	char					*str;

	path = ft_strjoin("/tmp/Minishell_DOC_", ft_itoa((int)index));
	fd = open(path, io_flag(RD_DOC), 0666);
	while (fd > 0)
	{
		str = readline("> ");
		if (!str)
			break ;
		if (ft_strcmp(str, delimiter))
			break ;
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	index++;
	close(fd);
	fd = open(path, io_flag(RD_DOC_READ));
	return (fd);
}
