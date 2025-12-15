/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 08:53:23 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/11/05 01:59:40 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_bonus.h"

int	all_info_checked(t_depot *depot)
{
	if (depot->path_to_ea && depot->path_to_no && depot->path_to_so
		&& depot->path_to_we && depot->c_colors_flag && depot->f_colors_flag
		&& depot->path_to_door)
		return (1);
	return (0);
}

int	read_map(int fd, t_depot *depot)
{
	char	**n_map;

	n_map = malloc(sizeof(char *) * 1);
	if (!n_map)
	{
		perror("malloc");
		return (1);
	}
	n_map[0] = NULL;
	if (read_map_loop(fd, &n_map))
		return (ft_split_free(n_map), 1);
	depot->map = n_map;
	if (map_clean(depot))
		return (1);
	if (map_parse(depot))
		return (1);
	return (0);
}

int	map_parse(t_depot *depot)
{
	char	**map;
	int		j;

	j = 0;
	map = depot->map;
	while (map[j])
	{
		if (check_map_row(map, j))
			return (1);
		j++;
	}
	if (player_point_parsing(depot))
		return (1);
	return (0);
}

int	player_point_parsing(t_depot *depot)
{
	char	**map;
	int		i;
	int		j;

	j = 0;
	map = depot->map;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			count_player_direction(map[j][i], depot);
			i++;
		}
		j++;
	}
	if (advanced_map_parsing(depot))
		return (1);
	return (0);
}

int	advanced_map_parsing(t_depot *depot)
{
	if (depot->ea + depot->no + depot->so + depot->we != 1)
	{
		ft_fprintf(2, "Only one player point allowed!\n");
		return (1);
	}
	if (doors_parsing(depot->map))
		return (1);
	if (ultra_map_parse(depot))
		return (1);
	pad_map_lines(depot->map);
	replace_spaces_tabs(depot->map);
	return (0);
}
