/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 08:53:23 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/07/29 17:08:18 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	all_info_checked(t_depot *depot)
{
	if (depot->path_to_EA && depot->path_to_NO
		&& depot->path_to_SO && depot->path_to_WE
			&& depot->c_colors_flag && depot->f_colors_flag)
		return (1);
	return (0);
}

int	read_map(int fd, t_depot *depot)
{
	char	*str;
	char	**n_map;

	str = NULL;
	n_map = malloc(sizeof(char *) * 1);
	if (!n_map)
	{
		perror("malloc");
		return (1);
	}
	n_map[0] = NULL;
	while (1)
	{
		str = ft_gnl(fd);
		if (!str)
			break ;
		if (*str == '\n' || *str == ' ')
			continue ;
		n_map = ft_realloc(n_map, str);
		if (!n_map)
			return (1);
		free(str);
	}
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
	int		i;
	int		j;

	i = 0;
	j = 0;
	map = depot->map;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] != '1' && map[j][i] != '0'
				&& map[j][i] != ' ' && map[j][i] != 'P'
					&& is_not_pp(map[j][i]))
			{
				ft_fprintf(2, "%c is an Invalid character!\n", map[j][i]);
				ft_split_free(depot->map);
				return (1);
			}
			i++;
		}
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

	i = 0;
	j = 0;
	map = depot->map;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == 'N')
				depot->NO += 1;
			if (map[j][i] == 'S')
				depot->SO += 1;
			if (map[j][i] == 'W')
				depot->WE += 1;
			if (map[j][i] == 'E')
				depot->EA += 1;
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
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (depot->EA + depot->NO
		+ depot->SO + depot->WE != 1)
	{
		ft_fprintf(2, "Only one player point allowed!\n");
		return (1);
	}
	while (depot->map[i])
	{
		j = 0;
		while (depot->map[i][j])
		{
			if (depot->map[i][j] == ' ')
				depot->map[i][j] = '1';
			j++;
		}
		i++;
	}
	if (ultra_map_parse(depot))
		return (1);
	return (0);
}
