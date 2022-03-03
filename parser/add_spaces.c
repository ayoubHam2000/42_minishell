/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:52:54 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/03 14:19:15 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*re(char *str)
{
	if ((*str == '>' && *(str + 1) == '>')
		|| (*str == '<' && *(str + 1) == '<')
		|| (*str == '<' && *(str + 1) == '>')
		)
		str = str + 2;
	else if (*str == '>' || *str == '<')
		str = str + 1;
	return (str);
}

static int	size_of_new_str(char *str)
{
	int	i;
	int	c;

	i = 0;
	while (*str)
	{
		c = re(str) - str;
		if(c > 0)
		{
			str = str + c;
			i = i + c + 2;
		}
		i++;
		str++;
	}
	return (i);
}

char	*add_spaces(char *str)
{
	char	*new;
	int		i;
	int		c;

	new = ft_malloc(size_of_new_str(str) + 1);
	i = 0;
	while (*str)
	{
		c = re(str) - str;
		if (c > 0)
		{
			new[i++] = ' ';
			while (c)
			{
				new[i++] = *str++;
				c--;
			}
			new[i++] = ' ';
		}
		else
			new[i++] = *str++;
	}
	new[i] = 0;
	return (new);
}
