/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunakim <sunakim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 15:13:37 by mnishimo          #+#    #+#             */
/*   Updated: 2019/05/25 15:54:40 by mnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	ignore_comment_gnl(char **line)
{
	int ret;

	while ((ret = get_next_line(0, line)) > 0)
	{
		if (!(**line))
		{
			free(*line);
			return (-1);
		}
		if (**line == '#' && !ft_strcmp(*line, "##start"))
			return (2);
		if (**line == '#' && !ft_strcmp(*line, "##end"))
			return (3);
		if (**line == '#' && *(*line + 1) == '#')
		{
			free(*line);
			return (-1);
		}
		if (**line != '#')
			return (1);
		print_free(*line);
	}
	return (ret);
}

static int	nbr_ants(t_lemin *lemin, char *line)
{
	int i;

	i = 0;
	if (!line)
		return (-1);
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != '+')
		{
			print_free(line);
			return (-1);
		}
		i++;
	}
	lemin->ants = ft_atollu(line);
	print_free(line);
	if ((long long)(lemin->ants) < 0)
		return (-1);
	return (1);
}

static int	start_end(t_lemin *lemin, char **line, int start)
{
	char	**split;
	t_room	*new;

	print_free(*line);
	if (start < 2 || start > 3 || (ignore_comment_gnl(line)) != 1)
		return (-1);
	split = ft_strsplit(*line, ' ');
	new = add_newroom(lemin, split);
	ft_deltab(split);
	if (!new || (start == 2 && lemin->s) || (start == 3 && lemin->e))
	{
		free(*line);
		return (-1);
	}
	if (start == 2)
		lemin->s = new;
	else
		lemin->e = new;
	return (1);
}

static int	store_edges(t_tnode **top, char *line)
{
	int		err;
	char	**split;

	if (!line || *line == '-')
		return (0);
	split = ft_strsplit(line, '-');
	print_free(line);
	err = (add_edge(top, split) == -1) ? 1 : 0;
	ft_deltab(split);
	if (err)
		return (-1);
	while (!err && (ignore_comment_gnl(&line)) == 1)
	{
		if (!line || *line == '-')
		{
			print_free(line);
			return (0);
		}
		split = ft_strsplit(line, '-');
		print_free(line);
		err = (add_edge(top, split) == -1) ? 1 : 0;
		ft_deltab(split);
	}
	return (0);
}

int			get_input(t_lemin *lemin)
{
	char	*line;
	char	**split;
	int		ret;
	t_room	*new;

	if ((ret = ignore_comment_gnl(&line)) != 1 || nbr_ants(lemin, line) < 0)
		return (-1);
	while ((ret = ignore_comment_gnl(&line)) >= 1)
	{
		if (ret > 1 && start_end(lemin, &line, ret) == -1)
			return (-1);
		else if (ret == 1)
		{
			split = ft_strsplit(line, ' ');
			new = add_newroom(lemin, split);
			ft_deltab(split);
			if (!new)
				return (store_edges(&(lemin->ntop), line));
		}
		print_free(line);
	}
	return (-1);
}
