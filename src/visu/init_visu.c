/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:46:24 by sunakim           #+#    #+#             */
/*   Updated: 2019/05/22 16:27:58 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void	init_texture(t_visu *vs)
{
	int i;

	i = 0;
	while (i < 5)
	{
		vs->text[i].mtexture = NULL;
		vs->text[i].mwidth = 0;
		vs->text[i].mheight = 0;
		vs->text[i].id = i;
		i++;
	}
}

static int	init(t_visu *vs)
{
	int img_flags;

	img_flags = IMG_INIT_PNG;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (0);
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		ft_error();
	vs->win = SDL_CreateWindow("LEMIN", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, S_W, S_H, SDL_WINDOW_SHOWN);
	if (vs->win == NULL)
		return (0);
	vs->rndr = SDL_CreateRenderer(vs->win, -1, SDL_RENDERER_ACCELERATED
			| SDL_RENDERER_PRESENTVSYNC);
	if (vs->rndr == NULL)
		return (0);
	SDL_SetRenderDrawColor(vs->rndr, 0, 0, 0, 255);
	if (!(IMG_Init(img_flags) & img_flags))
		return (0);
	return (1);
}

int			init_all(t_visu *vs, t_lemin *l)
{
	ft_bzero(vs, sizeof(t_visu));
	init_texture(vs);
	if (!init(vs))
		return (0);
	if (!load_media(vs->text, vs->rndr))
		return (0);
	if (!init_lemin(l, vs))
	{
		done_free(vs->win, vs->text, vs->rndr);
		return (0);
	}
	return (1);
}
