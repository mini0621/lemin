/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:35:27 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/23 12:01:00 by sunakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		print_free(char *line)
{
	if (line)
	{
		ft_putendl(line);
		free(line);
	}
}

static int	ft_error(void)
{
	ft_putstr("ERROR\n");
	return (0);
}

static void	del_lemin(t_lemin *lemin, t_list **solution)
{
	if (solution && *solution)
		ft_lstdel(solution, &delpath_lst);
	ft_treedel(&(lemin->ntop), &delroom);
	ft_treedel(&(lemin->ctop), NULL);
}

int			main(void)
{
	t_lemin	lemin;
	t_list	*solution;

	ft_bzero(&lemin, sizeof(t_lemin));
	solution = NULL;
	if (get_input(&lemin) < 0 || !(solution = solve(&lemin)))
	{
		del_lemin(&lemin, NULL);
		return (ft_error());
	}
	output(&lemin, &solution);
	del_lemin(&lemin, &solution);
	return (0);
}
