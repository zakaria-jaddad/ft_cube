/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 07:46:49 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/08/04 11:04:54 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	path_check_v2(char *path)
{
	char		*ext;
	int			le;

	if (!path)
		return (0);
	if (ft_strlen(path) <= 3)
	{
		write(2, "Invalid extension!\n", 20);
		return (0);
	}
	le = ft_strlen(path) - 1;
	ext = ft_substr(path, le - 4, le);
	if (!ext)
	{
		perror("malloc");
		return (0);
	}
	if (ft_strncmp(".png", ext, 4))
	{
		write(2, "Invalid extension!\n", 20);
		return (free(ext), 0);
	}
	free(ext);
	return (1);
}

int	path_check(char *path)
{
	if (!path)
		return (0);
	while (*path)
		path++;
	if (*(path - 4) == '.' && *(path - 3) == 'c'
		&& *(path - 2) == 'u' && *(path - 1) == 'b')
		return (1);
	else
		write(2, "Invalid extension!\n", 20);
	return (0);
}

int	clean_and_add_floor(char *str, t_depot *depot)
{
	char	*clean_colors;
	char	**split_colors;

	if (is_number(str))
		return (1);
	clean_colors = ft_strtrim(str, " \t\n");
	if (!clean_colors)
		return (perror("malloc"), 1);
	if (column_check(clean_colors))
	{
		free(clean_colors);
		return (1);
	}
	if (column_check(clean_colors))
	{
		free(clean_colors);
		return (1);
	}
	split_colors = ft_split(clean_colors, ',');
	free(clean_colors);
	if (!split_colors)
		return (perror("malloc"), 1);
	return (process_split_colors(split_colors, depot));
}

int	convert_and_add_floor(char **str, t_depot *depot)
{
	int	i;
	int	val;

	i = 0;
	while (str[i])
	{
		val = ft_atoi(str[i]);
		if (range_check(val))
		{
			if (assign_floor_color(depot, val, i))
				return (1);
		}
		else
			return (ft_fprintf(2, "Invalid colors range\n"), 1);
		i++;
	}
	depot->f_color = rgb_convert(depot->floor_color_r,
			depot->floor_color_g, depot->floor_color_b);
	depot->f_colors_flag = 1;
	return (0);
}

size_t	get_max_len(char **map, int rows)
{
	size_t	max_len;
	size_t	len;
	int		i;

	max_len = 0;
	i = 0;
	while (i < rows)
	{
		len = 0;
		if (map[i])
		{
			while (map[i][len])
				len++;
			if (len > max_len)
				max_len = len;
		}
		i++;
	}
	return (max_len);
}
