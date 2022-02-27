/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:22:52 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/28 00:09:23 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
ψ <=> A space or tab character
ϵ <=> \0
k <=> S

E -> N=C|C
N -> [a-Z_][a-Z0-9_]*
C -> [^|] | [ψ]C | TC | ϵ
T -> < | > | >> | << | | | W
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
	if (*str == '>' && *(str + 1) == '>')
		str = str + 2;
	else if (*str == '<' && *(str + 1) == '<')
		str = str + 2;
	else if (*str == '>' || *str == '<' || *str == '|')
		str = str + 1;
	else
		return (w_rule(str));
	if (*str == '>' || *str == '<' || *str == '|')
		return (NULL);
	return (str);
}

char	*c_rule(char *str)
{
	while (1)
	{
		if (!(*str))
			return (str);
		if (*str == '|')
			return (NULL);
		if (*str == ' ' || *str == '\t')
		{
			str++;
			continue ;
		}
		str = t_rule(str);
		if (!str)
			return (NULL);
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

char	*e_rule(char *str)
{
	char	*t;

	t = n_rule(str);
	if (t && *t == '=')
		return (c_rule(t + 1));
	return (c_rule(str));
}

int	parse_command(char *str, char **env)
{
	char	*res;

	res = expansion(str, env);
	str = e_rule(res);
	free(res);
	if (!str)
		printf("Syntax Error\n");
	else
		printf("%s\n", str);
	return (0);
}
