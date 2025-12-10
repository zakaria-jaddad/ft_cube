/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigrav <antigrav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:00:00 by antigrav          #+#    #+#             */
/*   Updated: 2025/12/08 17:00:00 by antigrav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	assign_floor_color(t_depot *depot, int color, int index)
{
	if (index == 0)
		depot->floor_color_r = color;
	else if (index == 1)
		depot->floor_color_g = color;
	else if (index == 2)
		depot->floor_color_b = color;
	else
		return (ft_fprintf(2, "More than 3 colors\n"), 1);
	return (0);
}

int	assign_ceiling_color(t_depot *depot, int color, int index)
{
	if (index == 0)
		depot->ceiling_color_r = color;
	else if (index == 1)
		depot->ceiling_color_g = color;
	else if (index == 2)
		depot->ceiling_color_b = color;
	else
		return (ft_fprintf(2, "More than 3 colors\n"), 1);
	return (0);
}

int	process_split_colors(char **split_colors, t_depot *depot)
{
	if (colors_parse(split_colors))
		return (ft_split_free(split_colors), 1);
	if (convert_and_add_floor(split_colors, depot))
		return (ft_split_free(split_colors), 1);
	ft_split_free(split_colors);
	return (0);
}

int	process_split_ceiling(char **split_colors, t_depot *depot)
{
	if (convert_and_add_ceiling(split_colors, depot))
		return (ft_split_free(split_colors), 1);
	ft_split_free(split_colors);
	return (0);
}

int	all_info_checked(t_depot *depot)
{
	if (depot->path_to_ea && depot->path_to_no && depot->path_to_so
		&& depot->path_to_we && depot->c_colors_flag && depot->f_colors_flag)
		return (1);
	return (0);
}
