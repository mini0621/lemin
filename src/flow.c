/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 00:03:56 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/25 15:58:37 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_list	*read_a_flow(t_path *p, t_lemin *lemin)
{
	t_list	*c;

	while (get_cur_room(p) != lemin->e)
	{
		c = (get_cur_room(p))->edge;
		while (c && ((t_edge *)(c->content))->flow != 1)
			c = c->next;
		if (c)
			appendflow(p, ((t_edge *)(c->content))->room);
		else
		{
			del_path(p);
			return (NULL);
		}
	}
	if (!(c = ft_lstnomallocnew((void *)p, sizeof(t_path *))))
	{
		del_path(p);
		return (NULL);
	}
	return (c);
}

t_list			*read_flows(t_lemin *lemin)
{
	t_list	*ret;
	t_path	*p;
	t_list	*cur;

	ret = NULL;
	cur = lemin->s->edge;
	while (cur)
	{
		if (((t_edge *)(cur->content))->flow == 1)
		{
			if (!(p = init_path(((t_edge *)(cur->content))->room)))
				return (NULL);
			ft_lstadd(&ret, read_a_flow(p, lemin));
		}
		cur = cur->next;
	}
	return (ret);
}

static void		change_flow(t_edge *edge, int i)
{
	if (i)
	{
		edge->flow = 0;
		edge->inverse->flow = 0;
	}
	else
	{
		edge->flow = 1;
		edge->inverse->flow = -1;
	}
}

int				argument_flow(t_lemin *lemin)
{
	t_room	*v;
	t_room	*p;
	t_list	*cur;
	t_edge	*edge;

	v = lemin->e;
	while (v != lemin->s)
	{
		p = v->label;
		cur = p->edge;
		while (cur)
		{
			edge = (t_edge *)(cur->content);
			if (edge->room == v)
			{
				if (edge->flow == -1)
					change_flow((t_edge *)(cur->content), 1);
				else if (edge->flow == 0)
					change_flow((t_edge *)(cur->content), 0);
			}
			cur = cur->next;
		}
		v = p;
	}
	return (1);
}

t_list			*se_connected(t_lemin *lemin)
{
	t_list	*cur;
	t_path	*p;

	if (!lemin->s || !lemin->e)
		return (NULL);
	cur = lemin->s->edge;
	while (cur && ((t_edge *)(cur->content))->room != lemin->e)
		cur = cur->next;
	if (!cur)
		return (NULL);
	if (!(p = init_path(lemin->e)))
		return (NULL);
	if (!(cur = ft_lstnomallocnew((void *)p, sizeof(t_path *))))
	{
		del_path(p);
		return (NULL);
	}
	return (cur);
}
