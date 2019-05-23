/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:14:57 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/22 13:42:54 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

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
