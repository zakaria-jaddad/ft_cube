/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_v3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:30:35 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/10 17:04:22 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	check_neighbors(char **map, int x, int y)
{
	if (map[x - 1][y] != '1' && map[x - 1][y] != '0'
		&& not_player_point(map[x - 1][y]))
		return (1);
	if (map[x + 1][y] != '1' && map[x + 1][y] != '0'
		&& not_player_point(map[x + 1][y]))
		return (1);
	if (map[x][y + 1] != '1' && map[x][y + 1] != '0'
		&& not_player_point(map[x][y + 1]))
		return (1);
	if (map[x][y - 1] != '1' && map[x][y - 1] != '0'
		&& not_player_point(map[x][y - 1]))
		return (1);
	return (0);
}

int	is_closed_by_walls(char **map)
{
	int	x;
	int	y;

	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == '0' || !not_player_point(map[x][y]))
			{
				if (check_neighbors(map, x, y))
				{
					ft_fprintf(2, "!Map Invalid\n");
					return (1);
				}
			}
			y++;
		}
		x++;
	}
	return (0);
}

int	not_player_point(char c)
{
	if (c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return (1);
	return (0);
}

int	retrieve_player_pos(t_depot *depot)
{
	int	i;
	int	j;

	i = 0;
	while (depot->map[i])
	{
		j = 0;
		while (depot->map[i][j])
		{
			if (!not_player_point(depot->map[i][j]))
			{
				depot->player_x = j;
				depot->player_y = i;
				depot->map[i][j] = '0';
				return (0);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	clean_path(t_depot *depot)
{
	depot->path_to_no = ft_strtrim(depot->path_to_no, "\n\t\r");
	depot->path_to_so = ft_strtrim(depot->path_to_so, "\n\t\r");
	depot->path_to_we = ft_strtrim(depot->path_to_we, "\n\t\r");
	depot->path_to_ea = ft_strtrim(depot->path_to_ea, "\n\t\r");
	if (!depot->path_to_ea || !depot->path_to_no || !depot->path_to_so
		|| !depot->path_to_we)
		return (1);
	return (0);
}
