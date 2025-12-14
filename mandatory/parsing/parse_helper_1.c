/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:14:17 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/08/04 11:06:50 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	clean_and_add_ceiling(char *str, t_depot *depot)
{
	char	*clean_colors;
	char	**split_colors;

	if (is_number(str))
		return (1);
	clean_colors = ft_strtrim(str, " \t");
	if (!clean_colors)
		return (perror("malloc"), 1);
	if (column_check(clean_colors))
	{
		free(clean_colors);
		return (1);
	}
	split_colors = ft_split(clean_colors, ',');
	free(clean_colors);
	if (!split_colors)
		return (perror("malloc"), 1);
	if (colors_parse(split_colors))
	{
		ft_split_free(split_colors);
		return (1);
	}
	return (process_split_ceiling(split_colors, depot));
}

int	convert_and_add_ceiling(char **str, t_depot *depot)
{
	int		i;
	int		val;

	i = 0;
	while (str[i])
	{
		val = ft_atoi(str[i]);
		if (range_check(val))
		{
			if (assign_ceiling_color(depot, val, i))
				return (1);
		}
		else
			return (ft_fprintf(2, "Invalid colors range\n"), 1);
		i++;
	}
	depot->c_color = rgb_convert(depot->ceiling_color_r,
			depot->ceiling_color_g, depot->ceiling_color_b);
	depot->c_colors_flag = 1;
	return (0);
}

int	is_color(char **str)
{
	if (!ft_strcmp("F", *str) || !ft_strcmp("C", *str))
		return (1);
	return (0);
}

int	player_point_count(t_depot *depot, int j)
{
	int		i;
	char	**map;

	map = depot->map;
	i = 0;
	while (map[j][i])
	{
		if (map[j][i] == 'N')
			depot->no += 1;
		if (map[j][i] == 'S')
			depot->so += 1;
		if (map[j][i] == 'W')
			depot->we += 1;
		if (map[j][i] == 'E')
			depot->ea += 1;
		i++;
	}
	return (0);
}
