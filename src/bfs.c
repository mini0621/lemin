/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 23:12:42 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/25 16:06:28 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	get_flow(t_room *room, int v)
{
	t_list	*cur;
	t_edge	*edge;

	cur = room->edge;
	while (cur)
	{
		edge = (t_edge *)(cur->content);
		if (edge->flow == 1 && room->label == edge->room && room->scanned == v)
			return (-1);
		else if (edge->flow == 1)
			return (1);
		cur = cur->next;
	}
	return (0);
}

static int	scan(t_room *room, t_queue *q, int v, int dir)
{
	t_list	*cur;
	t_list	*nl;
	t_edge	*edge;

	cur = room->edge;
	while (cur)
	{
		edge = (t_edge *)(cur->content);
		if (edge->room->scanned < v && ((dir != 1 && !edge->flow)
					|| (dir != 0 && edge->flow == -1)))
		{
			edge->room->label = room;
			edge->room->scanned = v;
			if ((nl = ft_lstnomallocnew((void *)(edge->room),
							sizeof(t_room *))))
				ft_qappend(q, nl);
			else
				return (-1);
		}
		cur = cur->next;
	}
	return (1);
}

int			bfs(t_lemin *lemin, t_queue *q, int net_flow)
{
	t_list	*rm;
	t_room	*room;

	if (!q || !q->top || !(rm = ft_qpop(q)))
		return (0);
	if (scan((t_room *)(rm->content), q, net_flow, 0) < 0)
		return (0);
	lemin->s->scanned = net_flow;
	ft_lstdelone(&rm, NULL);
	while ((rm = ft_qpop(q)))
	{
		room = (t_room *)(rm->content);
		if (room == lemin->e)
		{
			ft_lstdelone(&rm, NULL);
			return (1);
		}
		if (scan(room, q, net_flow, get_flow(room, net_flow)) < 0)
		{
			ft_lstdelone(&rm, NULL);
			return (0);
		}
		ft_lstdelone(&rm, NULL);
	}
	return ((lemin->e->scanned != net_flow) ? 0 : 1);
}
