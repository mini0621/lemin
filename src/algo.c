/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnishimo <mnishimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 22:42:00 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/20 18:24:07 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int		get_cost(t_lemin *lemin, t_list *sol)
{
	long long	cost;
	int			np;
	long long	ants;
	t_list		*cur;

	ft_lstsort(&(sol), &cmp_path_d);
	cur = sol;
	while (cur->next)
		cur = cur->next;
	cost = ((t_path *)(cur->content))->d;
	ants = (long long)(lemin->ants);
	np = 0;
	cur = sol;
	while (cur && ants > 0)
	{
		ants -= cost - ((t_path *)(cur->content))->d + 1;
		cur = cur->next;
		np++;
	}
	if (ants <= 0)
		return (cost);
	return (cost + (ants / np) + 1);
}

static int		better_sol(t_lemin *lemin, t_list **best,
		t_list **new, long long *best_cost)
{
	long long	tmp;

	tmp = get_cost(lemin, *new);
	if (!(*best) || *best_cost > tmp)
	{
		*best_cost = tmp;
		if (*best)
			ft_lstdel(best, &delpath_lst);
		*best = *new;
		*new = NULL;
		return (1);
	}
	return (0);
}

static t_list	*fail_solve(t_queue *q, t_list *best)
{
	ft_lstdel(&best, &delpath_lst);
	ft_qdel(&q, NULL);
	return (NULL);
}

static	t_queue	*init_solve(t_lemin *lemin, t_list **new,
		long long *cost)
{
	t_queue	*q;

	*new = NULL;
	*cost = -1;
	if (!lemin->s || !lemin->e
		|| !(q = ft_qnew()) || q_addstart(lemin->s, q) < 0)
		return (NULL);
	return (q);
}

t_list			*solve(t_lemin *lemin)
{
	t_queue		*q;
	t_list		*best;
	long long	cost;
	t_list		*new;

	if ((best = se_connected(lemin)))
		return (best);
	if (!(q = init_solve(lemin, &new, &cost)))
		return (NULL);
	while (bfs(lemin, q, lemin->nf) && argument_flow(lemin))
	{
		lemin->nf += 1;
		if (!(new = read_flows(lemin)))
			return (fail_solve(q, best));
		if (!better_sol(lemin, &best, &new, &cost))
			break ;
		if (q_addstart(lemin->s, q) < 0)
			return (NULL);
	}
	if (new)
		ft_lstdel(&new, &delpath_lst);
	ft_qdel(&q, NULL);
	if (cost < 0)
		ft_lstdel(&best, &delpath_lst);
	return (best);
}
