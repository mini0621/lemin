/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 15:13:37 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/23 15:50:27 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	add_rem(t_list *sol, int nf, int ants)
{
	t_list		*cur;

	cur = sol;
	while (cur)
	{
		if (ants % nf)
		{
			((t_path *)(cur->content))->d += ants / nf + 1;
			ants--;
		}
		else
			((t_path *)(cur->content))->d += ants / nf;
		cur = cur->next;
	}
}

static void	distribute_ants(t_lemin *lemin, t_list *sol)
{
	int			cost;
	long long	ants;
	t_list		*cur;

	cur = sol;
	while (cur->next)
		cur = cur->next;
	cost = ((t_path *)(cur->content))->d;
	ants = (long long)(lemin->ants);
	lemin->nf = 0;
	cur = sol;
	while (cur && ants > 0)
	{
		((t_path *)(cur->content))->d = cost
			- ((t_path *)(cur->content))->d + 1;
		ants -= ((t_path *)(cur->content))->d;
		cur = cur->next;
		lemin->nf += 1;
	}
	if (ants <= 0)
		return ;
	add_rem(sol, lemin->nf, ants);
}

static int	push_ants(unsigned long long ant, t_list *lst, char **op)
{
	char	*t;
	t_list	*cur;
	int		ant_tmp;
	int		ret;

	cur = lst;
	t = NULL;
	ret = 0;
	while (cur)
	{
		if (ant)
			ret++;
		if (ant && op && *op)
		{
			ft_asprintf(&t, " L%llu-%s", ant, ((t_room *)(cur->content))->name);
			*op = ft_strjoinfree(op, &t, 3);
		}
		else if (ant)
			ft_asprintf(op, "L%llu-%s", ant, ((t_room *)(cur->content))->name);
		ant_tmp = ((t_room *)(cur->content))->ant;
		((t_room *)(cur->content))->ant = ant;
		ant = ant_tmp;
		cur = cur->next;
	}
	return (ret);
}

static int	send_ants(t_path *p, unsigned long long *ant_nbr,
			t_lemin *lemin, char **output)
{
	char *tmp;

	if (p->d < 0)
		return (0);
	tmp = NULL;
	if (p->d && *ant_nbr <= lemin->ants)
	{
		push_ants(*ant_nbr, p->flow->top, output);
		p->d -= 1;
		*ant_nbr += 1;
	}
	else
	{
		if (!push_ants(0, p->flow->top, output))
			p->d = -1;
	}
	return (1);
}

void		output(t_lemin *lemin, t_list **solution)
{
	unsigned long long	ant_nbr;
	t_list				*cur;
	char				*output;

	ft_printf("\n");
	ant_nbr = 1;
	if (!((*solution)->next)
		&& ((t_path *)((*solution)->content))->flow->top->content == lemin->e)
		return (printsimple(lemin, ant_nbr));
	output = (char *)1;
	distribute_ants(lemin, *solution);
	while (output)
	{
		output = NULL;
		cur = *solution;
		while (cur)
		{
			if (!send_ants((t_path *)(cur->content), &ant_nbr, lemin, &output))
				return (free(output));
			cur = cur->next;
		}
		if (output)
			print_free(output);
	}
}
