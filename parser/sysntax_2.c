/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sysntax_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:38:50 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/01 14:48:28 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*c_rule(char *str)
{
	while (1)
	{
		if (!(*str))
			return (str);
		if (*str == '|')
			return (NULL);
		while (*str == '\t' || *str == ' ')
			str++;
		str = t_rule(str);
		if (!str)
			return (NULL);
		while (*str == '\t' || *str == ' ')
			str++;
		if (*str == '|')
		{
				str++;
			while (*str == '\t' || *str == ' ')
				str++;
			if (!(*str))
				return (NULL);
		}
	}
}

char	*n_rule(char *str)
{
	if ((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z') || (*str == '_'))
		str++;
	else
		return (NULL);
	while ((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z') || (*str == '_') || (*str >= '0' && *str <= '9'))
		str++;
	return (str);
}

char	*check_sysntax(char *str)
{
	char	*t;

	t = n_rule(str);
	if (t && *t == '=')
	{
		t++;
		while (*t == '\t' || *t == ' ')
			t++;
		if (!(*t))
			return (NULL);
		str = w_rule(t);
	}
	return (c_rule(str));
}
