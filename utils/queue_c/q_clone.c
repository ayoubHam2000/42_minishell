/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_clone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:41:43 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/04 20:31:22 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

t_queue	*q_empty_queue(t_queue *queue)
{
	t_queue	*new_queue;
	t_node	*node;

	new_queue = q_init();
	if (!new_queue)
		return (NULL);
	node = queue->first;
	while (node)
	{
		if (!q_enqueue(new_queue, NULL))
		{
			q_clear(new_queue, NULL);
			//free(new_queue);
			return (NULL);
		}
		node = node->next;
	}
	return (new_queue);
}

t_queue	*q_clone(t_queue *queue, void *(*clone_ptr)(void *p))
{
	t_queue	*new_queue;
	t_node	*node;
	t_node	*new_node;

	new_queue = q_empty_queue(queue);
	if (!new_queue)
		return (NULL);
	node = queue->first;
	new_node = new_queue->first;
	while (node)
	{
		if (node->p && clone_ptr)
			new_node->p = clone_ptr(node->p);
		node = node->next;
		new_node = new_node->next;
	}
	return (new_queue);
}
