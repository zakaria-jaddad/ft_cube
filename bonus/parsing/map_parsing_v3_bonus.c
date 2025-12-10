#include "../includes/parsing_bonus.h"

int	is_closed_by_walls(char **map)
{
	int	x;
	int	y;

	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == '0' || !not_player_point(map[x][y]))
			{
				if (check_surroundings(map, x, y))
					return (1);
			}
			y++;
		}
		x++;
	}
	return (0);
}

int	not_player_point(char c)
{
	if (c != 'N' && c != 'S' && c != 'W' && c != 'E')
		return (1);
	return (0);
}

int	retrieve_player_pos(t_depot *depot)
{
	int	i;
	int	j;

	i = 0;
	while (depot->map[i])
	{
		j = 0;
		while (depot->map[i][j])
		{
			if (!not_player_point(depot->map[i][j]))
			{
				depot->player_x = j;
				depot->player_y = i;
				depot->map[i][j] = '0';
				return (0);
			}
			j++;
		}
		i++;
	}
	return (0);
}

uint32_t	rgb_convert(int r, int g, int b)
{
	return (((uint32_t)(r & 0xFF) << 24) | ((uint32_t)(g & 0xFF) << 16)
		| ((uint32_t)(b & 0xFF) << 8) | 0xFFu);
}

int	clean_path(t_depot *depot)
{
	depot->path_to_no = ft_strtrim(depot->path_to_no, "\n\t\r");
	depot->path_to_so = ft_strtrim(depot->path_to_so, "\n\t\r");
	depot->path_to_we = ft_strtrim(depot->path_to_we, "\n\t\r");
	depot->path_to_ea = ft_strtrim(depot->path_to_ea, "\n\t\r");
	depot->path_to_door = ft_strtrim(depot->path_to_door, "\n\t\r");
	if (!depot->path_to_ea || !depot->path_to_no || !depot->path_to_so
		|| !depot->path_to_we)
		return (1);
	return (0);
}
