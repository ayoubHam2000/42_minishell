/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sysntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:38:41 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/05 12:59:22 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
ψ <=> A space or tab character
ϵ <=> \0
k <=> S

C -> [^|]ψ*Tψ*|C
T -> <ψ*W | >ψ*W | >>ψ*W | <<ψ*W | W
W -> 'A | "B | S
A -> .*?'
B -> .*?"
S -> ([^['"ψ|><]].)*
*/

static char	*s_rule(char *str)
{
	while (*str)
	{
		if (*str == ' ' || *str == '\t' || *str == '|' || *str == '>' \
			|| *str == '<' || *str == '\'' || *str == '"')
			return (str);
		str++;
	}
	return (str);
}

static char	*w_rule(char *str)
{
	char	*p;

	if (*str == '\'')
		p = ft_strchr(str + 1, '\'');
	else if (*str == '"')
		p = ft_strchr(str + 1, '"');
	else
		return (s_rule(str));
	if (p)
		return (p + 1);
	else
		return (NULL);
}

static char	*t_rule(char *str)
{
	char	*t;

	if (*str == '>' && *(str + 1) == '>')
		str = str + 2;
	else if (*str == '<' && *(str + 1) == '<')
		str = str + 2;
	else if (*str == '>' || *str == '<')
		str = str + 1;
	else
		return (w_rule(str));
	while (*str == ' ' || *str == '\t')
		str++;
	t = w_rule(str);
	if (t - str)
		str = t;
	else
		return (NULL);
	return (str);
}

char	*check_sysntax(char *str)
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
