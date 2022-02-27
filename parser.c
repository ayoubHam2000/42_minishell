/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:22:52 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/24 16:33:18 by aben-ham         ###   ########.fr       */
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
		return (str + 2);
	else if (*str == '<' && *(str + 1) == '<')
		return (str + 2);
	else if (*str == '>' || *str == '<' || *str == '|')
		return (str + 1);
	return (w_rule(str));
}

char	*c_rule(char *str)
{
	if (!(*str))
		return (str);
	if (*str == '|')
		return (NULL);
	if (*str == ' ' || *str == '\t')
		return (c_rule(str));
	str = t_rule(str);
	return (c_rule(str));
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
	if (*t == '=')
		return (c_rule(t + 1));
	return (c_rule(str));
}

char	*next_dollar(char *str)
{
	char	*res;
	int		flag;

	res = str;
	flag = 1;
	while (*res)
	{
		if (*res == '\'')
		{
			flag = !flag;
			continue;
		}
		if (*res == '$' && flag)
		{
			return (res);	
		}
		res++;
	}
	return (NULL);
}

char	*get_env_var(char *str, char **env)
{
	return (ft_strjoin(str, ft_strdup(" _env_var")));
}

char	*add_dollar_content(t_queue *queue, char *str, char **env)
{
	char	*p;
	char	*env_var;

	p = n_rule(str);
	if (!p)
		return (NULL);
	p = ft_substr(str, 0, p - str);
	if (!p)
		return (NULL);
	env_var = get_env_var(p, env); //if not found in env it's value will be ""
	free(p);
	if (!q_enqueue(queue, env_var))
		return (NULL);
	return (str);
}

char	*merge_strings(t_queue	*queue)
{
	t_node	*node;
	size_t	len;
	char	*res;

	len = 0;
	node = queue->first;
	while (node)
	{
		len += ft_strlen(node->p);
		node = node->next;
	}
	res = malloc(len + 1);
	if (!res)
		ft_error(ERR_MEM);
	len = 0;
	node = queue->first;
	while (node)
	{
		ft_strlcpy(res + len, node->p, ft_strlen(node->p));
		len = ft_strlen(res);
		node = node->next;
	}
	return (res);
}

char	*expansion(char *str, char **env)
{
	t_queue	*queue;
	char	*token;
	char	*dollar;
	
	queue = q_init();
	dollar = next_dollar(str);
	while (dollar)
	{
		token = ft_substr(str, 0, dollar - str);
		if (!token || !q_enqueue(queue, token) || !add_dollar_content(queue, dollar + 1, env))
			ft_error(ERR_MEM);
		str = n_rule(dollar + 1);
		dollar = next_dollar(str);
	}
	str = merge_strings(queue);
	q_clear(queue, NULL);
	free(queue);
	return (str);
}

int	parse_command(char *str, char **env)
{
	char	*res;

	str = expansion(str, env);
	res = e_rule(str);
	printf("%s\n", res);
	return (0);
}
