/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_enqueue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:25:43 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/02 15:05:31 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

int	q_enqueue(t_queue *queue, void *p)
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
	return (1);
}
