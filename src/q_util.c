/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   q_util.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 22:47:04 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/18 18:17:28 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	q_addstart(t_room *start, t_queue *q)
{
	t_list	*nl;

	if (!q || !start)
		return (-1);
	ft_qclear(&q, NULL);
	if (!(nl = ft_lstnew(NULL, sizeof(t_room *))))
		return (-1);
	nl->content = start;
	if (!ft_qappend(q, nl))
	{
		free(nl);
		ft_qdel(&q, NULL);
		return (-1);
	}
	return (1);
}
