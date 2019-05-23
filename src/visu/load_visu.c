/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:49:56 by sunakim           #+#    #+#             */
/*   Updated: 2019/05/23 17:17:41 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	text_renderer(t_text *text, SDL_Rect rect, SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, text->mtexture, NULL, &rect);
}

int		load_from_file(char *path, t_text *text, SDL_Renderer *rndr, int size)
{
	int				success;
	SDL_Surface		*loaded_sur;

	success = 1;
	loaded_sur = IMG_Load(path);
	if (loaded_sur == NULL)
		ft_printf("Unable to load image\n");
	else
	{
		SDL_SetColorKey(loaded_sur, SDL_TRUE,
			SDL_MapRGB(loaded_sur->format, 0, 0xFF, 0xFF));
		text->mtexture = SDL_CreateTextureFromSurface(rndr, loaded_sur);
		if (text->mtexture == NULL)
			ft_printf("Unable to create texture\n");
		else
		{
			text->mwidth = loaded_sur->w / size;
			text->mheight = loaded_sur->h / size;
		}
		SDL_FreeSurface(loaded_sur);
	}
	if (text->mtexture == NULL)
		success = 0;
	return (success);
}

int		load_media(t_text *text, SDL_Renderer *renderer)
{
	if (!load_from_file("./src/visu/images/ant_robot33.png",
				&text[0], renderer, 2))
		return (0);
	if (!load_from_file("./src/visu/images/end_dark.png",
				&text[1], renderer, 2))
		return (0);
	if (!load_from_file("./src/visu/images/glow_dark.png",
				&text[2], renderer, 2))
		return (0);
	if (!load_from_file("./src/visu/images/ant_man2.png",
				&text[3], renderer, 11))
		return (0);
	if (!load_from_file("./src/visu/images/back8.jpg",
				&text[4], renderer, 4))
		return (0);
	return (1);
}
