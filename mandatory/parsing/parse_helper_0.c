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
	char	*ext;
	int		le;

	if (!path)
		return (0);
	if (ft_strlen(path) <= 3)
	{
		write(2, "Invalid extension!\n", 20);
		return (0);
	}
	le =  ft_strlen(path) - 1;
	ext = ft_substr(path, le - 4, le );
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
	char	**splitted_colors;

	if (is_number(str))
		return (1);
	printf("%s\n", str);
	clean_colors = ft_strtrim(str, " \t\n");
	if (!clean_colors)
	{
		perror("malloc");
		return (1);
	}
	printf("--> %s\n", clean_colors);
	splitted_colors = ft_split(clean_colors, ',');
	free(clean_colors);
	for(int i =0;splitted_colors[i];i++)
		printf("%s\n", splitted_colors[i]);
	if (!splitted_colors)
	{
		perror("malloc");
		return (1);
	}
	if (colors_parse(splitted_colors))
	{
		ft_split_free(splitted_colors);
		return (1);
	}
	if (convert_and_add_floor(splitted_colors, depot))
	{
		ft_split_free(splitted_colors);
		return (1);
	}
	ft_split_free(splitted_colors);
	return (0);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (!ft_isdigit(str[i]) && str[i] != ',' && str[i] != '\n')
		{
			ft_fprintf(2, "%s\n", "Colors should be digits");
			return (1);
		}
		i++;
	}
	return (0);
}

int	convert_and_add_floor(char **str, t_depot *depot)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (range_check(ft_atoi(str[i])))
		{
			if (i == 0)
				depot->floor_color_R = ft_atoi(str[i]);
			else if (i == 1)
				depot->floor_color_G = ft_atoi(str[i]);
			else if (i == 2)
				depot->floor_color_B = ft_atoi(str[i]);
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
	depot->f_color = rgb_convert(depot->floor_color_R,
		depot->floor_color_G, depot->floor_color_B);
	depot->f_colors_flag = 1;
	printf("FLOOR COLOR AZBI -> %d\n", depot->f_color);
	return (0);
}
