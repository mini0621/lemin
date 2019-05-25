/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:00:05 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/25 16:52:02 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

int		init_lemin(t_lemin *lemin, t_visu *vs)
{
	ft_bzero(lemin, sizeof(t_lemin));
	lemin->max_x = -2147483648;
	lemin->min_x = 2147483647;
	lemin->min_y = 2147483647;
	lemin->max_y = -2147483648;
	lemin->room_count = 0;
	if (get_input(lemin) < 0)
		return (0);
	if (lemin->room_count >= 30)
		ft_printf("Too many rooms to visualize\n");
	lemin->scale_x = (S_W - PAD * 2) / (lemin->max_x - lemin->min_x);
	lemin->scale_y = (S_H - PAD * 2) / (lemin->max_y - lemin->min_y);
	if (read_line(&(lemin->sol), lemin, vs) < 0)
	{
		del_lemin(lemin);
		return (0);
	}
	return (1);
}

void	del_lemin(t_lemin *lemin)
{
	ft_treedel(&(lemin->ntop), &deltreeroom);
	ft_lstdel(&(lemin->edges), &del_edge);
	ft_lstdel(&(lemin->sol), &del_line);
}
