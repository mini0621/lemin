/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 22:08:31 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/21 17:53:16 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_edge	*edge_new(t_room *room)
{
	t_edge	*new;

	if (!(new = (t_edge *)malloc(sizeof(t_edge))))
		return (NULL);
	new->room = room;
	new->flow = 0;
	return (new);
}

static int		is_dup(t_room *l, t_room *r)
{
	t_list	*cur;

	cur = l->edge;
	while (cur)
	{
		if (((t_edge *)(cur->content))->room == r)
			return (1);
		cur = cur->next;
	}
	cur = r->edge;
	while (cur)
	{
		if (((t_edge *)(cur->content))->room == l)
			return (1);
		cur = cur->next;
	}
	return (0);
}

int				add_edge(t_tnode **top, char **split)
{
	t_list	*n;
	t_tnode	*r;
	t_tnode	*l;
	t_edge	*tmp;

	if (!split || !split[0] || !split[1] || split[2]
			|| !(l = ft_avlfind(*top, split[0], &cmptnode_withname))
			|| !(r = ft_avlfind(*top, split[1], &cmptnode_withname))
			|| l == r || is_dup((t_room *)(l->cnt), (t_room *)(r->cnt)))
		return (-1);
	if (!(n = ft_lstnew(NULL, sizeof(t_edge *))))
		return (-1);
	n->content = edge_new(l->cnt);
	tmp = (t_edge *)(n->content);
	ft_lstadd(&(((t_room *)(r->cnt))->edge), n);
	if (!(n = ft_lstnew(NULL, sizeof(t_edge *))))
		return (-1);
	n->content = edge_new(r->cnt);
	((t_edge *)(n->content))->inverse = tmp;
	tmp->inverse = (t_edge *)(n->content);
	ft_lstadd(&(((t_room *)(l->cnt))->edge), n);
	return (0);
}
