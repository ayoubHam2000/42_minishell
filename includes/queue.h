/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-ham <aben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:53:12 by aben-ham          #+#    #+#             */
/*   Updated: 2022/03/04 20:31:22 by aben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_node	t_node;
struct s_node
{
	void	*p;
	t_node	*next;
};

typedef struct s_queue	t_queue;
struct s_queue
{
	t_node	*first;
	t_node	*last;
	long	len;
};

void	*ft_malloc(size_t size);

//NULL if malloc failed
void	*q_init(void);

//0 if s_push malloc failed
int		q_enqueue(t_queue *queue, void *p);

////free the pointer after remove it from the queue.
void	*q_dequeue(t_queue *queue);

/*
* NULL if the creating of Nodes failed
* if clone_ptr is NULL => all pointers of the cloned queue will be NULL
*/
t_queue	*q_clone(t_queue *queue, void *(*clone_ptr)(void *p));

void	q_clear(t_queue *queue, void (*del_ptr)(void *p));

#endif
