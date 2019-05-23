/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 15:13:37 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/23 16:57:01 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static int	ignore_comment_gnl(char **line)
{
	int ret;

	while ((ret = get_next_line(0, line)) > 0)
	{
		if (ft_strcmp(*line, "") == 0)
		{
			free(*line);
			return (3);
		}
		if (*line && **line == '#')
		{
			if ((ft_strcmp(*line, "##start")) == 0
				|| (ft_strcmp(*line, "##end") == 0))
				return (2);
			else
				free(*line);
		}
		else
			return (1);
	}
	return (ret);
}

static void	nbr_ants(t_lemin *lemin, char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) == 0 && line[i] != '+')
			ft_error();
		i++;
	}
	lemin->ants = ft_atollu(line);
	free(line);
}

static int	start_end(t_lemin *lemin, char **line)
{
	char	**split;
	int		start;
	t_room	*new;

	if ((ft_strcmp(*line, "##start")) == 0)
		start = 1;
	else
		start = ((ft_strcmp(*line, "##end")) == 0) ? 0 : -1;
	free(*line);
	if (start == -1 || (ignore_comment_gnl(line)) != 1)
		return (-1);
	split = ft_strsplit(*line, ' ');
	new = add_newroom(lemin, split);
	ft_deltab(split);
	if (new == NULL || (start == 1 && lemin->s != NULL)
		|| (start != 1 && lemin->e != NULL))
	{
		free(*line);
		return (-1);
	}
	if (start == 1)
		lemin->s = new;
	else
		lemin->e = new;
	return (1);
}

static int	store_edges(t_lemin *lemin, char **split, char *line)
{
	int	err;
	int	ret;

	free(line);
	lemin->edges = NULL;
	err = (add_edge(lemin, split) == -1) ? 1 : 0;
	ft_deltab(split);
	while (!err && (ret = ignore_comment_gnl(&line)) >= 1)
	{
		if (ret == 3)
			break ;
		if (!err && ret == 1)
		{
			split = ft_strsplit(line, '-');
			free(line);
			err = (add_edge(lemin, split) == -1) ? 1 : 0;
			ft_deltab(split);
		}
	}
	return (0);
}

int			get_input(t_lemin *lemin)
{
	char	*line;
	char	**split;
	t_room	*new;
	int		ret;

	if ((ret = ignore_comment_gnl(&line)) <= 0)
		return (-1);
	nbr_ants(lemin, line);
	while ((ret = ignore_comment_gnl(&line)) >= 1)
	{
		if (ret == 3)
			return (3);
		else if (ret == 2 && start_end(lemin, &line) == -1)
			return (-1);
		else if (ret != 2 && ret != 3)
		{
			split = ft_strsplit(line, ' ');
			new = add_newroom(lemin, split);
			ft_deltab(split);
			if (!new)
				return (store_edges(lemin, ft_strsplit(line, '-'), line));
		}
		free(line);
	}
	return (-1);
}
