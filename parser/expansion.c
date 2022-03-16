/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:49:02 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/16 02:06:04 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*var_pattern(char *str)
{
	if ((*str >= 'a' && *str <= 'z')
		|| (*str >= 'A' && *str <= 'Z') || (*str == '_'))
		str++;
	else
	{
		if (*str == '?')
			return (str + 1);
		return (NULL);
	}
	while ((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z')
		|| (*str == '_') || (*str >= '0' && *str <= '9'))
		str++;
	return (str);
}

static char	*next_dollar(char *str)
{
	char	*res;

	res = str;
	while (*res)
	{
		if (*res == '$' && var_pattern(res + 1))
			return (res);
		res++;
	}
	return (NULL);
}

static void	add_dollar_content(t_queue *queue, char *str)
{
	char	*p;
	char	*env_var;

	p = var_pattern(str);
	p = ft_substr(str, 0, p - str);
	env_var = ft_getenv(p);
	if (!env_var)
		env_var = ft_strdup("");
	else
		env_var = ft_strdup(env_var);
	q_enqueue(queue, env_var);
}

static char	*merge_strings(t_queue	*queue)
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
	res = ft_malloc(len + 1);
	len = 0;
	node = queue->first;
	while (node)
	{
		ft_strlcpy(res + len, node->p, ft_strlen(node->p) + 1);
		len = ft_strlen(res);
		node = node->next;
	}
	return (res);
}

char	*expansion(char *str)
{
	t_queue	*queue;
	char	*token;
	char	*dollar;

	if (str[0] == '\'')
		return (ft_strdup(str));
	queue = q_init();
	dollar = next_dollar(str);
	while (dollar)
	{
		token = ft_substr(str, 0, dollar - str);
		q_enqueue(queue, token);
		add_dollar_content(queue, dollar + 1);
		str = var_pattern(dollar + 1);
		dollar = next_dollar(str);
	}
	token = ft_substr(str, 0, ft_strlen(str));
	q_enqueue(queue, token);
	str = merge_strings(queue);
	return (str);
}
