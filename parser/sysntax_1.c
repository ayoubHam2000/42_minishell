/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   systax_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:38:41 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/01 14:46:58 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
ψ <=> A space or tab character
ϵ <=> \0
k <=> S

E -> (N=ψ*W)?C
N -> [a-Z_][a-Z0-9_]*
C -> [^|]ψ*Tψ*|C
T -> <ψ*W | >ψ*W | >>ψ*W | <<ψ*W | W
W -> 'A | "B | S
A -> .*?'
B -> .*?"
S -> ([^['"ψ|><]].)*
*/

char	*a_rule(char *str)
{
	while (*str && *str != '\'')
		str++;
	if (!(*str))
		return (NULL);
	return (str + 1);
}

char	*b_rule(char *str)
{
	while (*str && *str != '"')
		str++;
	if (!(*str))
		return (NULL);
	return (str + 1);
}

char	*s_rule(char *str)
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

char	*w_rule(char *str)
{
	if (*str == '\'')
		return (a_rule(str + 1));
	else if (*str == '"')
		return (b_rule(str + 1));
	return (s_rule(str));
}

char	*t_rule(char *str)
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
