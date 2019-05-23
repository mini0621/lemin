/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_cp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:05:24 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/23 16:57:52 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

void	del_sol(void *cnt, size_t size)
{
	if (size == sizeof(t_sol *))
		free(cnt);
}

void	del_line(void *cnt, size_t size)
{
	if (size == sizeof(t_line *))
	{
		ft_lstdel(&(((t_line *)cnt)->s), &del_sol);
		free(cnt);
	}
}

void	del_edge(void *cnt, size_t size)
{
	if (!size)
		return ;
	free(cnt);
}

void	delroom(void *cnt, size_t size)
{
	t_room	*room;

	if (!size)
		return ;
	room = (t_room *)cnt;
	ft_strdel(&(room->name));
	free(room);
}

void	deltreeroom(void *cnt)
{
	delroom(cnt, sizeof(t_room *));
}
