#include "../includes/parsing_bonus.h"

size_t	get_max_width(char **map, int rows)
{
	size_t	max_len;
	size_t	len;
	int		i;

	max_len = 0;
	i = 0;
	while (i < rows)
	{
		if (map[i])
		{
			len = 0;
			while (map[i][len])
				len++;
			if (len > max_len)
				max_len = len;
		}
		i++;
	}
	return (max_len);
}

void	create_new_line(char **line_ptr, size_t max_len)
{
	char	*newp;
	size_t	len;

	newp = malloc(max_len + 1);
	if (!newp)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	len = 0;
	while (len < max_len)
	{
		newp[len] = '1';
		len++;
	}
	newp[max_len] = '\0';
	*line_ptr = newp;
}

void	pad_one_line(char **line_ptr, size_t max_len)
{
	char	*newp;
	size_t	len;

	len = 0;
	while ((*line_ptr)[len])
		len++;
	if (len < max_len)
	{
		newp = realloc(*line_ptr, max_len + 1);
		if (!newp)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}
		while (len < max_len)
		{
			newp[len] = '1';
			len++;
		}
		newp[max_len] = '\0';
		*line_ptr = newp;
	}
}

void	count_player_direction(char c, t_depot *depot)
{
	if (c == 'N')
		depot->NO += 1;
	if (c == 'S')
		depot->SO += 1;
	if (c == 'W')
		depot->WE += 1;
	if (c == 'E')
		depot->EA += 1;
}
