/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:14:57 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/18 17:59:51 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		cmptnode_byname(void *cnt1, void *cnt2)
{
	if (cnt1 && cnt2)
	{
		if (((t_room *)cnt1)->name && ((t_room *)cnt2)->name)
			return (ft_strcmp(((t_room *)cnt1)->name, ((t_room *)cnt2)->name));
	}
	return (0);
}

int		cmptnode_withname(void *name, void *content)
{
	if (name && content)
	{
		if (name && ((t_room *)content)->name)
			return (ft_strcmp(name, ((t_room *)content)->name));
	}
	return (0);
}

int		cmptnode_bycoord(void *cnt1, void *cnt2)
{
	long long	ret;

	if (cnt1 && cnt2)
	{
		if ((ret = ((t_room *)cnt1)->coor - ((t_room *)cnt2)->coor) < 0)
			return (-1);
		return ((ret == 0) ? 0 : 1);
	}
	return (0);
}

int		cmp_path_d(void *c1, void *c2)
{
	if (c1 && c2)
		return (((t_path *)c1)->d - ((t_path *)c2)->d);
	return (0);
}
