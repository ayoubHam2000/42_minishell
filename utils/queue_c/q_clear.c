/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_clear.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:39:08 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/05 14:06:59 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

static void	default_del_ptr(void *p)
{
	free(p);
}

void	q_clear(t_queue *queue, void (*del_ptr)(void *p))
{
	t_node	*node;
	t_node	*target;

	if (!queue)
		return ;
	if (!del_ptr)
		del_ptr = default_del_ptr;
	node = queue->first;
	while (node)
	{
		target = node;
		node = node->next;
		del_ptr(target->p);
		free(target);
	}
	queue->first = NULL;
	queue->last = NULL;
	queue->len = 0;
}
