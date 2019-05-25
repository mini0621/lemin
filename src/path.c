/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 17:05:14 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/25 14:38:12 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_path	*init_path(t_room *start)
{
	t_path	*np;
	t_list	*nl;

	if ((np = (t_path *)malloc(sizeof(t_path))) == NULL)
		return (NULL);
	np->d = 1;
	np->flow = ft_qnew();
	if (!(nl = ft_lstnomallocnew((void *)start, sizeof(t_room *))))
	{
		free(np->flow);
		free(np);
		return (NULL);
	}
	ft_qappend(np->flow, nl);
	return (np);
}

void	del_path(t_path *path)
{
	ft_qdel(&(path->flow), NULL);
	free(path);
}

void	appendflow(t_path *path, t_room *room)
{
	t_list	*nl;

	if (!path || !room)
		return ;
	path->d += 1;
	if (!(nl = ft_lstnomallocnew((void *)room, sizeof(t_room *))))
		return ;
	ft_qappend(path->flow, nl);
}

t_room	*get_cur_room(t_path *p)
{
	return ((t_room *)(p->flow->last->content));
}
