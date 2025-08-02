#include "../includes/parsing.h"

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
				if (map[x - 1][y] != '1' && map[x - 1][y] != '0' && not_player_point(map[x - 1][y]))
				{
					ft_fprintf(2, "!Map Invalid\n");
					return (1);
				}
				if (map[x + 1][y] != '1' && map[x + 1][y] != '0' && not_player_point(map[x + 1][y]))
				{
					ft_fprintf(2, "!Map Invalid\n");
					return (1);
				}
				if (map[x][y + 1] != '1' && map[x ][y + 1] != '0' && not_player_point(map[x][y + 1]))
				{
					ft_fprintf(2, "!Map Invalid\n");
					return (1);
				}
				if (map[x][y - 1] != '1' && map[x][y - 1] != '0' && not_player_point(map[x][y - 1]))
				{
					ft_fprintf(2, "!Map Invalid\n");
					return (1);
				}
			}
			y++;
		}
		x++;
	}
	return (0);
}

int	not_player_point(char c)
{
	if (c != 'N' && c != 'S'
		&& c != 'W' && c != 'E')
		return (1);
	return (0);
}

int	retreive_player_pos(t_depot *depot)
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
				depot->player_x = i;
				depot->player_y = j;
				depot->map[i][j] = '0';
				//return (0);
			}
			j++;
		}
		i++;
	}
	return (0);
}
