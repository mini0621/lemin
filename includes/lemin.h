/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:35:52 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/23 17:09:22 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "../libftprintf/includes/libftprintf.h"

typedef struct	s_room
{
	char				*name;
	long long			coor;
	int					scanned;
	t_list				*edge;
	struct s_room		*label;
	unsigned long long	ant;
}				t_room;

typedef struct	s_edge
{
	int				flow;
	t_room			*room;
	struct s_edge	*inverse;
}				t_edge;

typedef struct	s_lemin
{
	unsigned long long	ants;
	t_tnode				*ntop;
	t_tnode				*ctop;
	t_room				*s;
	t_room				*e;
	int					nf;
}				t_lemin;

typedef struct	s_path
{
	long long	d;
	t_queue		*flow;
}				t_path;

int				get_input(t_lemin *lemin);

t_list			*solve(t_lemin *lemin);
int				bfs(t_lemin *lemin, t_queue *q, int net_flow);
int				argument_flow(t_lemin *lemin);
t_list			*read_flows(t_lemin *lemin);
t_list			*se_connected(t_lemin *lemin);
int				q_addstart(t_room *start, t_queue *q);

int				cmptnode_byname(void *cnt1, void *cnt2);
int				cmptnode_withname(void *name, void *content);
int				cmptnode_bycoord(void *cnt1, void *cnt2);
int				cmp_path_d(void *c1, void *c2);
int				cmp_path_alt(void *c1, void *c2);

t_room			*add_newroom(t_lemin *lemin, char **split);
void			free_room(t_room *room);

int				add_edge(t_tnode **top, char **split);

void			print_free(char *line);
void			output(t_lemin *lemin, t_list **solution);
void			printsimple(t_lemin *lemin, unsigned long long ant_nbr);

t_path			*init_path(t_room	*start);
void			del_path(t_path *path);
void			appendflow(t_path *path, t_room *room);
t_room			*get_cur_room(t_path *p);

void			delpath_lst(void *content, size_t size);
void			delroom(void *cnt);
void			del_edge(void *content, size_t size);
#endif
