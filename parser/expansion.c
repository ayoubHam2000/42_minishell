/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:49:02 by aben-ham          #+#    #+#             */
/*   Updated: 2022/02/28 15:21:41 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_var(char *str, char **env)
{
	return (ft_strjoin(str, "_env_var"));
}

static char	*var_pattern(char *str)
{
	if ((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z') || (*str == '_'))
		str++;
	else
		return (NULL);
	while ((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z') || (*str == '_') || (*str >= '0' && *str <= '9'))
		str++;
	return (str);
}

static char	*next_dollar(char *str)
{
	char	*res;
	int		flag;

	res = str;
	flag = 1;
	while (*res)
	{
		if (*res == '\'')
			flag = !flag;
		if (*res == '$' && flag && var_pattern(res + 1))
			return (res);
		res++;
	}
	return (NULL);
}

static int	add_dollar_content(t_queue *queue, char *str, char **env)
{
	char	*p;
	char	*env_var;

	p = var_pattern(str);
	p = ft_substr(str, 0, p - str);
	if (!p)
		return (ft_error(ERR_MEM));
	env_var = get_env_var(p, env);
	free(p);
	if (!env_var)
		return (ft_error(ERR_ENV_VAR));
	if (!q_enqueue(queue, env_var))
		return (ft_error(ERR_MEM));
	return (1);
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
	res = malloc(len + 1);
	if (!res)
		return (ft_error(ERR_MEM));
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
		if (!token || !q_enqueue(queue, token))
			return (ft_error(ERR_MEM));
		if (!add_dollar_content(queue, dollar + 1, env))
			return (NULL);
		str = var_pattern(dollar + 1);
		dollar = next_dollar(str);
	}
	token = ft_substr(str, 0, ft_strlen(str));
	if (!token || !q_enqueue(queue, token))
		return ((void *)ft_error(ERR_MEM));
	str = merge_strings(queue);
	if (!str)
		return (NULL);
	q_clear(queue, NULL);
	free(queue);
	return (str);
}
