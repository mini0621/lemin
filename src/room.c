/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 17:53:27 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/20 15:32:00 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static long long	convert_coord(int x, int y)
{
	long long ret;
	long long tmp;

	ret = (long long)y;
	tmp = (long long)x;
	ret = ret << 32;
	ret = (ret | tmp);
	return (ret);
}

static int			is_valid_coord(char *coord)
{
	int	i;

	i = 0;
	while (coord[i])
	{
		if (!ft_isdigit(coord[i]) && coord[i] != '-' && coord[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

static t_room		*room_new(char **split)
{
	t_room *new;

	if (!split || !split[0] || !split[1] || !split[2] || split[3]
			|| !is_valid_coord(split[1]) || !is_valid_coord(split[2])
			|| **split == 'L' || ft_strchr(split[0], '-')
			|| !(new = (t_room *)ft_memalloc(sizeof(t_room))))
		return (NULL);
	if (!(new->name = ft_strdup(split[0])))
	{
		free(new);
		return (NULL);
	}
	new->coor = convert_coord(ft_atoi(split[1]), ft_atoi(split[2]));
	new->scanned = -1;
	new->edge = NULL;
	new->ant = 0;
	return (new);
}

t_room				*add_newroom(t_lemin *lemin, char **split)
{
	t_room	*nr;
	t_tnode	*nn;

	if (!(nr = room_new(split)))
		return (NULL);
	if (!(nn = ft_avlnew(NULL, 0)))
	{
		free_room(nr);
		return (NULL);
	}
	nn->cnt = nr;
	if (!(ft_avladd(&(lemin->ntop), nn, &cmptnode_byname, &delroom)))
		return (NULL);
	if (!(nn = ft_avlnew(NULL, 0)))
		return (NULL);
	nn->cnt = nr;
	if (!(ft_avladd(&(lemin->ctop), nn, &cmptnode_bycoord, NULL)))
		return (NULL);
	return (nr);
}

void				free_room(t_room *room)
{
	ft_strdel(&(room->name));
	if (room->edge)
		ft_lstdel(&(room->edge), &del_edge);
	free(room);
}
