/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:43:09 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/08/02 07:23:45 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	map_clean(t_depot *depot)
{
	int	i;

	i = 0;
	while (depot->map[i])
	{
		depot->map[i] = ft_strtrim(depot->map[i], "\n");
		if (!depot->map[i])
		{
			perror("malloc");
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_not_pp(char c)
{
	if (c != 'N' && c != 'S'
		&& c != 'W' && c != 'E')
		return (1);
	return (0);
}

int	three_elements_check(char **splitted_colors)
{
	int	i;
	
	i = 0;
	while (splitted_colors[i])
		i++;
	if (i != 3)
	{
		ft_fprintf(2, "Provide no more than 3 colors\n");
		return (1);
	}
	return (0);
}
int	colors_parse(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i != 3)
	{
		ft_fprintf(2, "More than three colors!\n");
		return (1);
	}
	return (0);
}

int	ultra_map_parse(t_depot *depot)
{
	char	**map;
	int		x;
	int		y;
	int		row_len;
	int		column_len;

	x = 0;
	y = 0;
	map = depot->map;
	column_len = ft_dbl_strlen(map) - 1;
	while (map[x])
	{
		y = 0;
		row_len = ft_strlen(map[x]) - 1;
		printf("==> %s\n", map[x]);
		while (map[x][y])
		{
			if (map[x][0] != '1' || map[x][row_len] != '1')
			{
				ft_fprintf(2, "Map Invalid!\n");
				return (1);
			}
			if (all_ones(map[0]) || all_ones(map[column_len]))
			{
				ft_fprintf(2, "Map Invalid!\n");
				return (1);
			}
			y++;
		}
		x++;
	}
	if (is_closed_by_walls(map))
		return (1);
	return (0);
}

int	all_ones(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1')
			return (1);
		i++;
	}
	return (0);
}
