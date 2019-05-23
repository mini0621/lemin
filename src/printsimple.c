/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printsimple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:17:42 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/23 17:54:32 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	printsimple(t_lemin *lemin, unsigned long long ant_nbr)
{
	if (!lemin->ants)
		return ;
	ft_printf("L%llu-%s", ant_nbr, lemin->e->name);
	ant_nbr++;
	while (ant_nbr <= lemin->ants)
	{
		ft_printf(" L%llu-%s", ant_nbr, lemin->e->name);
		ant_nbr++;
	}
	ft_printf("\n");
}
