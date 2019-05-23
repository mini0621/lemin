/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 14:48:26 by sunakim           #+#    #+#             */
/*   Updated: 2019/05/22 15:37:55 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int		get_width(t_text *text)
{
	return (text->mwidth);
}

int		get_height(t_text *text)
{
	return (text->mheight);
}

void	set_color(Uint8 red, Uint8 green, Uint8 blue, t_text *text)
{
	SDL_SetTextureColorMod(text->mtexture, red, green, blue);
}

void	set_blendmode(SDL_BlendMode blending, t_text *text)
{
	SDL_SetTextureBlendMode(text->mtexture, blending);
}

void	set_alpha(Uint8 alpha, t_text *text)
{
	SDL_SetTextureAlphaMod(text->mtexture, alpha);
}
