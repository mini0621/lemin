/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:07:25 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/23 15:40:08 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int			ft_error(void)
{
	ft_putstr("ERROR\n");
	return (0);
}

static void	move_ants(t_lemin *l, t_visu *vs, t_list *lst)
{
	t_list	*cur;

	cur = ((t_line *)(lst->content))->s;
	while (cur)
	{
		move_render(vs, (t_sol *)(cur->content), l);
		cur = cur->next;
	}
	l->button += 1;
}

static void	visu(t_visu *vs, t_lemin *l)
{
	t_list *lst;

	lst = l->sol;
	if (!l->sol)
		return ;
	while (!vs->quit)
	{
		SDL_SetRenderDrawColor(vs->rndr, 0, 0, 0, 0xFF);
		SDL_RenderClear(vs->rndr);
		draw_edges(l->edges, vs->rndr, l, vs->text);
		draw_rooms(l->ntop, vs->rndr, vs->text, l);
		while (SDL_PollEvent(&(vs->e)) != 0)
		{
			if (vs->e.type == SDL_QUIT)
				vs->quit = 1;
			dot_handle_event(&(vs->e), &lst, l);
		}
		if (l->button >= 1)
			move_ants(l, vs, lst);
		SDL_RenderPresent(vs->rndr);
	}
}

int			main(int argc, char **argv)
{
	t_lemin	l;
	t_visu	vs;
	char	*theme;

	if (argc != 1)
	{
		theme = argv[1];
	}
	if (!init_all(&vs, &l))
		return (ft_error());
	else
		visu(&vs, &l);
	del_lemin(&l);
	done_free(vs.win, vs.text, vs.rndr);
	return (0);
}
