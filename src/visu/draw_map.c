/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 15:35:17 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/22 15:57:46 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int			draw_edges(t_list *top, SDL_Renderer *rndr, t_lemin *l, t_text *t)
{
	t_list		*cur;
	t_edge		*edge;
	SDL_Rect	rect;

	if (!rndr)
		return (-1);
	rect.x = 0;
	rect.y = 0;
	rect.h = 1300;
	rect.w = 1300;
	text_renderer(&t[4], rect, rndr);
	cur = top;
	while (cur)
	{
		edge = (t_edge *)(cur->content);
		SDL_SetRenderDrawColor(rndr, 66, 238, 244, 0xFF);
		SDL_RenderDrawLine(rndr, (edge->r1->x - l->min_x) * l->scale_x + PAD,
			(edge->r1->y - l->min_y) * l->scale_y + PAD,
			(edge->r2->x - l->min_x) * l->scale_x + PAD,
			(edge->r2->y - l->min_y) * l->scale_y + PAD);
		cur = cur->next;
	}
	return (1);
}

static int	set_rooms(t_tnode *root, SDL_Renderer *rndr, t_text *t, t_lemin *l)
{
	SDL_Rect	rect;
	int			i;

	if (((t_room *)(root->cnt)) == l->s)
		i = 0;
	else if (((t_room *)(root->cnt)) == l->e)
		i = 1;
	else
		i = 2;
	rect.x = (((t_room *)(root->cnt))->x - l->min_x) * l->scale_x
				- t[i].mwidth / 2 + PAD;
	rect.y = (((t_room *)(root->cnt))->y - l->min_y) * l->scale_y
				- t[i].mheight / 2 + PAD;
	rect.w = t[i].mwidth;
	rect.h = t[i].mheight;
	text_renderer(&t[i], rect, rndr);
	if (root->r)
		set_rooms(root->r, rndr, t, l);
	if (root->l)
		set_rooms(root->l, rndr, t, l);
	return (1);
}

int			draw_rooms(t_tnode *r, SDL_Renderer *rndr, t_text *t, t_lemin *l)
{
	if (r == NULL)
		return (1);
	set_rooms(l->ntop, rndr, t, l);
	return (1);
}
