/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:20:39 by aben-ham          #+#    #+#             */
/*   Updated: 2022/04/12 23:38:32 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ft_q_enqueue(t_queue *queue, void *p)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (0);
	new->p = p;
	new->next = NULL;
	if (!queue->first)
	{
		queue->first = new;
		queue->last = new;
	}
	else
	{
		queue->last->next = new;
		queue->last = new;
	}
	queue->len++;
	return (1);
}

static void	*ft_q_init(void)
{
	t_queue	*new_queue;

	new_queue = malloc(sizeof(t_queue));
	if (!new_queue)
		return (NULL);
	new_queue->first = NULL;
	new_queue->last = NULL;
	new_queue->len = 0;
	return (new_queue);
}

static void	add_addresse(void *p, int free)
{
	static t_queue	*queue;

	if (free)
		q_clear(queue, NULL);
	else
	{
		if (!queue)
		{
			queue = ft_q_init();
			if (!queue)
				ft_error_exit(ERR_MALLOC);
		}
		if (!ft_q_enqueue(queue, p))
			ft_error_exit(ERR_MALLOC);
	}
}

void	free_all(void)
{
	add_addresse(NULL, 1);
}

void	*ft_malloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (!p)
		ft_error_exit("MALLOC");
	add_addresse(p, 0);
	return (p);
}
