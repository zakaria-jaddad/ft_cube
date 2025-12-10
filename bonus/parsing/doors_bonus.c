#include "../includes/parsing_bonus.h"

static int	check_door_validity(char **map, size_t i, size_t j, size_t len)
{
	if (i == len || i == 0)
		return (1);
	if (j == 0 || j == (ft_strlen(map[i]) - 1))
		return (1);
	if (!((map[i - 1][j] == '1' && map[i + 1][j] == '1')
		|| (map[i][j + 1] == '1' && map[i][j - 1] == '1')))
		return (1);
	return (0);
}

int	doors_parsing(char **map)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	len = ft_dbl_strlen(map) - 1;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'D')
			{
				if (check_door_validity(map, i, j, len))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
