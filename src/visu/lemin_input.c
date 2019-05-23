/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 17:53:27 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/23 14:42:40 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static t_room	*room_new(char *name, int x, int y, t_lemin *lemin)
{
	t_room *new;

	if (!name || !(new = (t_room *)ft_memalloc(sizeof(t_room))) || *name == 'L'
		|| ft_strchr(name, '-') || !(new->name = ft_strdup(name)))
		return (NULL);
	new->x = x;
	new->y = y;
	lemin->max_x = ft_max(x, lemin->max_x);
	lemin->max_y = ft_max(y, lemin->max_y);
	lemin->min_x = ft_min(x, lemin->min_x);
	lemin->min_y = ft_min(y, lemin->min_y);
	new->ant = 0;
	return (new);
}

t_room			*add_newroom(t_lemin *l, char **split)
{
	t_room	*nr;
	t_tnode	*nn;

	if (!split || !split[0] || !split[1] || !split[2] || split[3]
		|| !(nr = room_new(split[0], ft_atoi(split[1]), ft_atoi(split[2]), l)))
		return (NULL);
	if (!(nn = ft_avlnew(NULL, 0)))
	{
		delroom((void *)nr, sizeof(t_room *));
		return (NULL);
	}
	nn->cnt = nr;
	if (!(ft_avladd(&(l->ntop), nn, &cmptnode_byname, &deltreeroom)))
		return (NULL);
	l->room_count += 1;
	return (nr);
}

static t_edge	*new_edge(void *l, void *r)
{
	t_edge	*ret;

	ret = (t_edge *)malloc(sizeof(t_edge));
	if (ret)
	{
		ret->r1 = (t_room *)r;
		ret->r2 = (t_room *)l;
	}
	return (ret);
}

int				add_edge(t_lemin *lemin, char **split)
{
	t_list	*n;
	t_tnode	*r;
	t_tnode	*l;

	if (!split || !split[0] || !split[1] || split[2]
			|| !(l = ft_avlfind(lemin->ntop, split[0], &cmptnode_withname))
			|| !(r = ft_avlfind(lemin->ntop, split[1], &cmptnode_withname))
			|| l == r)
		return (-1);
	if (!(n = ft_lstnew(NULL, sizeof(void *))))
		return (-1);
	if (!(n->content = new_edge(l->cnt, r->cnt)))
	{
		free(n);
		return (-1);
	}
	n->content_size = sizeof(t_edge *);
	ft_lstadd(&(lemin->edges), n);
	return (0);
}
