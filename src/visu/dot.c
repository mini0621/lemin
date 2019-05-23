/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 10:48:03 by sunakim           #+#    #+#             */
/*   Updated: 2019/05/23 16:59:47 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void		dot_handle_event(SDL_Event *e, t_list **lst, t_lemin *l)
{
	t_list	*c;

	if (e->type == SDL_KEYDOWN && e->key.repeat == 0)
	{
		if (e->key.keysym.sym == SDLK_RIGHT && (*lst)->next)
			*lst = (*lst)->next;
		if (e->key.keysym.sym == SDLK_LEFT
			&& ((t_line *)((*lst)->content))->prev)
			*lst = ((t_line *)((*lst)->content))->prev;
		if (e->key.keysym.sym == SDLK_SPACE)
			l->button = 1;
		else
		{
			c = ((t_line *)((*lst)->content))->s;
			while (c)
			{
				((t_sol *)(c->content))->d_x = ((t_sol *)(c->content))->start_x;
				((t_sol *)(c->content))->d_y = ((t_sol *)(c->content))->start_y;
				c = c->next;
			}
		}
		ft_printf("line nbr: %i\n", ((t_line *)((*lst)->content))->line_nbr);
	}
}

static void	render_ant(t_sol *sol, t_text *text, SDL_Renderer *rndr)
{
	SDL_Rect rect;

	rect.x = sol->d_x + text[3].mwidth / 2;
	rect.y = sol->d_y + text[3].mheight / 10;
	rect.w = text[3].mwidth;
	rect.h = text[3].mheight;
	text_renderer(&text[3], rect, rndr);
}

void		move_render(t_visu *vs, t_sol *sol, t_lemin *l)
{
	if (l->button == 1)
	{
		sol->d_x = sol->start_x;
		sol->d_y = sol->start_y;
	}
	if (l->button >= 1 && l->button <= 100)
	{
		sol->d_x += sol->d_vx;
		sol->d_y += sol->d_vy;
		render_ant(sol, vs->text, vs->rndr);
	}
	else if (l->button > 100)
		render_ant(sol, vs->text, vs->rndr);
}
