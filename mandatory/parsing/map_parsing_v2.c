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

int	three_elements_check(char **split_colors)
{
	int	i;

	i = 0;
	while (split_colors[i])
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
	int		column_len;

	map = depot->map;
	column_len = ft_dbl_strlen(map) - 1;
	if (check_horizontal_walls(map, column_len))
		return (1);
	if (check_vertical_walls(map))
		return (1);
	if (is_closed_by_walls(map))
		return (1);
	pad_map_lines(depot->map);
	return (0);
}
