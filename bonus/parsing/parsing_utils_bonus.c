/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:34:26 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/10 16:34:27 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_bonus.h"

int	process_line(char *line, t_depot *depot)
{
	if (!line || *line == '\n')
		return (0);
	if (parse_line(line, depot))
		return (1);
	if (all_info_checked(depot))
	{
		if (clean_path(depot))
			return (1);
		return (2);
	}
	return (0);
}

int	read_map_loop(int fd, char ***n_map)
{
	char	*str;

	while (1)
	{
		str = ft_gnl(fd);
		if (!str)
			break ;
		if (*str != '\n')
		{
			*n_map = ft_realloc(*n_map, str);
			if (!*n_map)
			{
				free(str);
				return (1);
			}
		}
		if (*str == '\n' && ft_dbl_strlen(*n_map) > 0)
		{
			free(str);
			return (ft_fprintf(2, "Ivalid Map!\n"), 1);
		}
		free(str);
	}
	return (0);
}

int	check_map_row(char **map, int j)
{
	int	i;

	i = 0;
	while (map[j][i])
	{
		if (map[j][i] != '1' && map[j][i] != '0' && map[j][i] != ' '
			&& map[j][i] != 'P' && is_not_pp(map[j][i])
			&& map[j][i] != '\t' && map[j][i] != 'D')
		{
			ft_fprintf(2, "%c is an Invalid character!\n", map[j][i]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	replace_spaces_tabs(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ' || map[i][j] == '\t')
				map[i][j] = '1';
			j++;
		}
		i++;
	}
}

int	check_rows(char **map, int x, int column_len)
{
	int	y;
	int	row_len;

	y = 0;
	row_len = ft_strlen(map[x]) - 1;
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
	return (0);
}
