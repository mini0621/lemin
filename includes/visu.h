/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:35:52 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/22 17:23:13 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISU_H
# define VISU_H

# include "libftprintf.h"
# include <SDL.h>
# include <SDL_image.h>
# include <string.h>

# define S_W 1300
# define S_H 1300
# define PAD 100
# define D_W 20
# define D_H 20
# define D_V 10

typedef struct	s_room
{
	char	*name;
	float	x;
	float	y;
	int		ant;
}				t_room;

typedef struct	s_sol
{
	int		nbr_ant;
	t_room	*rm;
	float	start_x;
	float	start_y;
	float	d_x;
	float	d_y;
	float	d_vx;
	float	d_vy;
}				t_sol;

typedef struct	s_line
{
	int		line_nbr;
	t_list	*s;
	t_list	*prev;
}				t_line;

typedef struct	s_lemin
{
	int		ants;
	t_tnode	*ntop;
	t_list	*edges;
	t_room	*s;
	t_room	*e;
	int		i;
	int		max_x;
	int		max_y;
	int		min_x;
	int		min_y;
	int		scale_x;
	int		scale_y;
	int		button;
	int		room_count;
	t_list	*sol;
}				t_lemin;

typedef struct	s_edge
{
	t_room	*r1;
	t_room	*r2;
}				t_edge;

typedef struct	s_text
{
	SDL_Texture		*mtexture;
	int				mheight;
	int				mwidth;
	int				id;
}				t_text;

typedef struct	s_visu
{
	SDL_Window		*win;
	SDL_Renderer	*rndr;
	SDL_Event		e;
	t_text			text[5];
	int				quit;
}				t_visu;

int				init_lemin(t_lemin *lemin, t_visu *vs);
void			del_lemin(t_lemin *lemin);

int				get_input(t_lemin *lemin);
int				add_edge(t_lemin *lemin, char **split);
int				ft_error(void);

int				cmptnode_byname(void *cnt1, void *cnt2);
int				cmptnode_withname(void *name, void *content);

t_room			*add_newroom(t_lemin *lemin, char **split);

void			delroom(void *cnt, size_t size);
void			deltreeroom(void *cnt);
void			del_edge(void *cnt, size_t size);
void			del_sol(void *cnt, size_t size);
void			del_line(void *cnt, size_t size);

int				draw_edges(t_list *top, SDL_Renderer *rndr, t_lemin *l,
				t_text *t);
int				draw_rooms(t_tnode *r, SDL_Renderer *rndr, t_text *t,
				t_lemin *l);

int				init_all(t_visu *vs, t_lemin *l);

void			text_renderer(t_text *text, SDL_Rect rect,
				SDL_Renderer *renderer);
int				load_from_file(char *path, t_text *text, SDL_Renderer *rndr,
				int size);
int				load_media(t_text *text, SDL_Renderer *renderer);

int				get_width(t_text *text);
int				get_height(t_text *text);
void			set_color(Uint8 red, Uint8 green, Uint8 blue, t_text *text);
void			set_blendmode(SDL_BlendMode blending, t_text *text);
void			set_alpha(Uint8 alpha, t_text *text);

void			free_t_text(t_text *text);
void			free_texture(t_text *text);
void			done_free(SDL_Window *window, t_text *text,
				SDL_Renderer *renderer);

int				read_line(t_list **s, t_lemin *l, t_visu *vs);
void			move_render(t_visu *vs, t_sol *sol, t_lemin *l);
void			dot_handle_event(SDL_Event *e, t_list **lst, t_lemin *l);
#endif
