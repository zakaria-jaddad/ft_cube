/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:34:17 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/10 16:34:18 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_bonus.h"

int	is_bad_neighbor(char c)
{
	if (c != '1' && c != '0' && not_player_point(c) && c != 'D')
		return (1);
	return (0);
}

int	check_surroundings(char **map, int x, int y)
{
	if (is_bad_neighbor(map[x - 1][y]) || is_bad_neighbor(map[x + 1][y]) ||
		is_bad_neighbor(map[x][y - 1]) || is_bad_neighbor(map[x][y + 1]))
	{
		ft_fprintf(2, "!Map Invalid\n");
		return (1);
	}
	return (0);
}

int	ultra_map_parse(t_depot *depot)
{
	char	**map;
	int		x;
	int		column_len;

	x = 0;
	map = depot->map;
	column_len = ft_dbl_strlen(map) - 1;
	while (map[x])
	{
		if (check_rows(map, x, column_len))
			return (1);
		x++;
	}
	if (is_closed_by_walls(depot->map))
		return (1);
	return (0);
}

char	**extract_floor_data(char *str)
{
	char	*clean_colors;
	char	**splitted_colors;

	clean_colors = ft_strtrim(str, " \t\n");
	if (!clean_colors)
	{
		perror("malloc");
		return (NULL);
	}
	splitted_colors = ft_split(clean_colors, ',');
	free(clean_colors);
	if (!splitted_colors)
	{
		perror("malloc");
		return (NULL);
	}
	return (splitted_colors);
}

int	assign_floor_color(char *color_str, int index, t_depot *depot)
{
	int	color_val;

	color_val = ft_atoi(color_str);
	if (!range_check(color_val))
	{
		ft_fprintf(2, "%s\n", "Invalid colors range");
		return (1);
	}
	if (index == 0)
		depot->floor_color_r = color_val;
	else if (index == 1)
		depot->floor_color_g = color_val;
	else if (index == 2)
		depot->floor_color_b = color_val;
	else
	{
		ft_fprintf(2, "%s\n", "More than 3 colors");
		return (1);
	}
	return (0);
}
