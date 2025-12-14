/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:30:23 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/10 16:30:26 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	pad_map_lines_n(char **map, int rows)
{
	size_t	max_len;
	int		i;

	if (!map || rows <= 0)
		return ;
	max_len = get_max_len(map, rows);
	i = 0;
	while (i < rows)
	{
		if (map[i])
			pad_existing_line(map, i, max_len);
		else
			pad_null_line(map, i, max_len);
		i++;
	}
}

void	pad_map_lines(char **map)
{
	int	rows;

	rows = 0;
	if (!map)
		return ;
	while (map[rows])
		rows++;
	pad_map_lines_n(map, rows);
}

int	check_horizontal_walls(char **map, int last_row_idx)
{
	if (all_ones(map[0]) || all_ones(map[last_row_idx]))
	{
		ft_fprintf(2, "Map Invalid!\n");
		return (1);
	}
	return (0);
}

int	check_vertical_walls(char **map)
{
	int	x;
	int	row_len;

	x = 0;
	while (map[x])
	{
		row_len = ft_strlen(map[x]) - 1;
		if (map[x][0] != '1' || map[x][row_len] != '1')
		{
			ft_fprintf(2, "Map Invalid!\n");
			return (1);
		}
		x++;
	}
	return (0);
}

int	all_ones(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ' && str[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}
