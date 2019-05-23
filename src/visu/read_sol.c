/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_sol.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:11:22 by sunakim           #+#    #+#             */
/*   Updated: 2019/05/23 17:05:38 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static void		copy_prev_coor(t_lemin *l, t_sol *sol, t_list *prev, t_visu *vs)
{
	t_list	*cur;

	if (prev)
	{
		cur = ((t_line *)(prev->content))->s;
		while (cur && ((t_sol *)(cur->content))->nbr_ant != sol->nbr_ant)
			cur = cur->next;
		if (cur)
		{
			sol->start_x = ((t_sol *)(cur->content))->rm->x;
			sol->start_x = (sol->start_x - l->min_x) * l->scale_x
							- vs->text[3].mwidth + PAD;
			sol->start_y = ((t_sol *)(cur->content))->rm->y;
			sol->start_y = (sol->start_y - l->min_y) * l->scale_y
							- vs->text[3].mheight / 2 + PAD;
			return ;
		}
	}
	sol->start_x = (l->s->x - l->min_x) * l->scale_x
					- vs->text[3].mwidth + PAD;
	sol->start_y = (l->s->y - l->min_y) * l->scale_y
					- vs->text[3].mheight / 2 + PAD;
}

static int		sol_ant(char *split, t_sol *sol, t_visu *vs, t_lemin *l)
{
	t_tnode	*nd;
	t_room	*rm;
	char	**sp;
	float	tmp;

	if (!(sp = ft_strsplit(split, '-')))
		return (-1);
	if (!(nd = ft_avlfind(l->ntop, sp[1], &cmptnode_withname)))
	{
		ft_deltab(sp);
		return (-1);
	}
	ft_deltab(sp);
	rm = (t_room *)(nd->cnt);
	sol->rm = (t_room *)(nd->cnt);
	tmp = (rm->x - l->min_x) * l->scale_x - vs->text[3].mwidth + PAD;
	sol->d_vx = (tmp - sol->start_x) / 100;
	tmp = (rm->y - l->min_y) * l->scale_y - vs->text[3].mheight / 2 + PAD;
	sol->d_vy = (tmp - sol->start_y) / 100;
	return (1);
}

static t_list	*new_sol(t_lemin *l, char **split, t_list *prev, t_visu *vs)
{
	t_list	*s;
	t_list	*nl;
	t_sol	*ns;

	s = NULL;
	while (*split != NULL)
	{
		if (!(ns = (t_sol *)malloc(sizeof(t_sol))))
			return (NULL);
		ns->nbr_ant = ft_atoi(*split + 1);
		copy_prev_coor(l, ns, prev, vs);
		if (sol_ant(*split, ns, vs, l) < 0
			|| !(nl = ft_lstnew(NULL, sizeof(t_line *))))
		{
			free(ns);
			ft_lstdel(&s, &del_sol);
			return (NULL);
		}
		nl->content = ns;
		nl->content_size = sizeof(ns);
		ft_lstpushback(&s, nl);
		split++;
	}
	return (s);
}

static t_list	*new_line(char **split, t_list *prev, t_lemin *l, t_visu *vs)
{
	t_line	*new;
	t_list	*nl;

	if (!(new = (t_line *)malloc(sizeof(t_line))))
		return (NULL);
	if (!(new->s = new_sol(l, split, prev, vs)))
	{
		free(new);
		return (NULL);
	}
	new->prev = prev;
	if (!(nl = ft_lstnew(NULL, sizeof(t_line *))))
	{
		ft_lstdel(&(new->s), &del_sol);
		free(new);
		return (NULL);
	}
	nl->content = new;
	nl->content_size = sizeof(new);
	if (prev)
		new->line_nbr = ((t_line *)(prev->content))->line_nbr + 1;
	else
		new->line_nbr = 1;
	return (nl);
}

int				read_line(t_list **s, t_lemin *l, t_visu *vs)
{
	char	*line;
	char	**split;
	t_list	*nl;
	t_list	*prev;

	line = NULL;
	prev = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (!(*line) || *line != 'L' || !(split = ft_strsplit(line, ' ')))
		{
			free(line);
			continue ;
		}
		free(line);
		if (!(nl = new_line(split, prev, l, vs)))
		{
			ft_deltab(split);
			return (-1);
		}
		ft_deltab(split);
		ft_lstpushback(s, nl);
		prev = nl;
	}
	return (1);
}
