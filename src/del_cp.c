/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_cp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:05:24 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/18 18:01:54 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	delpath_lst(void *content, size_t size)
{
	if (content && size)
		del_path((t_path *)(content));
}

void	delroom(void *cnt)
{
	free_room((t_room *)cnt);
}

void	del_edge(void *content, size_t size)
{
	if (content && size)
		free((t_edge *)content);
}
