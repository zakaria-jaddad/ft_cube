#include "../includes/parsing_bonus.h"

void	pad_map_lines_n(char **map, int rows)
{
	size_t	max_len;
	int		i;

	if (!map || rows <= 0)
		return ;
	max_len = get_max_width(map, rows);
	i = 0;
	while (i < rows)
	{
		if (map[i])
			pad_one_line(&map[i], max_len);
		else
			create_new_line(&map[i], max_len);
		i++;
	}
}

void	pad_map_lines(char **map)
{
	int	rows;

	rows = 0;
	if (!map)
		return ;
	while (map[rows])
		rows++;
	pad_map_lines_n(map, rows);
}

uint32_t	rgba_convert(int r, int g, int b, int a)
{
	return (((uint32_t)(r & 0xFF) << 24) | ((uint32_t)(g & 0xFF) << 16)
		| ((uint32_t)(b & 0xFF) << 8) | ((uint32_t)(a & 0xFF)));
}
