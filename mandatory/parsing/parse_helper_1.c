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

int	range_check(int	color)
{
	if (color <= 255 && color >= 0)
		return (1);
	return (0);
}

int	clean_and_add_ceiling(char *str, t_depot *depot)
{
	char	*clean_colors;
	char	**split_colors;

	if (is_number(str))
		return (1);
	clean_colors = ft_strtrim(str, " \t");
	if (!clean_colors)
	{
		perror("malloc");
		return (1);
	}
	split_colors = ft_split(clean_colors, ',');
	if (!split_colors)
	{
		perror("malloc");
		return (1);
	}
	if (convert_and_add_ceiling(split_colors, depot))
	{
		ft_split_free(split_colors);
		return (1);
	}
	ft_split_free(split_colors);
	return (0);
}

int	convert_and_add_ceiling(char **str, t_depot *depot)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (range_check(ft_atoi(str[i])))
		{
			if (i == 0)
				depot->ceiling_color_R = ft_atoi(str[i]);
			else if (i == 1)
				depot->ceiling_color_G = ft_atoi(str[i]);
			else if (i == 2)
				depot->ceiling_color_B = ft_atoi(str[i]);
			else
			{
				ft_fprintf(2, "%s\n", "More than 3 colors");
				return (1);
			}
		}
		else
			return (ft_fprintf(2, "%s\n", "Invalid colors range"), 1);
		i++;
	}
	depot->c_color = rgb_convert(depot->ceiling_color_R,
		depot->ceiling_color_G, depot->ceiling_color_B);
	depot->c_colors_flag = 1;
	printf("CEILLING COLOR AZBI -> %d\n", depot->c_color);
	return (0);
}

int	is_color(char **str)
{
	if (!ft_strcmp("F", *str) || !ft_strcmp("C", *str))
		return (1);
	return (0);
}

int	is_map(char *str, t_depot *depot)
{
	int	i;

	i = 0;
	if (!depot->path_to_EA)
	while (str[i])
	{
		if (str[i] != '1')
			return (0);
		i++;
	}
	return (1);
}
