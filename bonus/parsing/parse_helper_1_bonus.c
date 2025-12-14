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

#include "../includes/parsing_bonus.h"

int	range_check(int color)
{
	if (color <= 255 && color >= 0)
		return (1);
	return (0);
}

int	clean_and_add_ceiling(char *str, t_depot *depot)
{
	char	*clean_colors;
	char	**splitted_colors;

	if (is_number(str))
		return (1);
	clean_colors = ft_strtrim(str, " \t");
	if (!clean_colors)
		return (perror("malloc"), 1);
	splitted_colors = ft_split(clean_colors, ',');
	if (!splitted_colors)
	{
		free(clean_colors);
		perror("malloc");
		return (1);
	}
	free(clean_colors);
	if (colors_parse(splitted_colors))
	{
		ft_split_free(splitted_colors);
		return (1);
	}
	if (convert_and_add_ceiling(splitted_colors, depot))
	{
		ft_split_free(splitted_colors);
		return (1);
	}
	ft_split_free(splitted_colors);
	return (0);
}

int	convert_and_add_ceiling(char **str, t_depot *depot)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (assign_ceiling_color(str[i], i, depot))
			return (1);
		i++;
	}
	depot->c_color = rgb_convert(depot->ceiling_color_r, depot->ceiling_color_g,
			depot->ceiling_color_b);
	depot->c_colors_flag = 1;
	return (0);
}

int	is_color(char **str)
{
	if (!ft_strcmp("F", *str) || !ft_strcmp("C", *str))
		return (1);
	return (0);
}
