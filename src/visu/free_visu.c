/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:47:24 by sunakim           #+#    #+#             */
/*   Updated: 2019/05/22 18:46:34 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	free_texture(t_text *text)
{
	if (text->mtexture != NULL)
	{
		SDL_DestroyTexture(text->mtexture);
		text->mtexture = NULL;
		text->mwidth = 0;
		text->mheight = 0;
	}
}

void	done_free(SDL_Window *window, t_text *text, SDL_Renderer *renderer)
{
	int i;

	i = 0;
	while (i < 5)
	{
		free_texture(&text[i]);
		i++;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	IMG_Quit();
	SDL_Quit();
}
