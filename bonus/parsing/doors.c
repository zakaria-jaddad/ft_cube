#include "../includes/parsing.h"

int doors_parsing(char **map)
{
	printf("======================================== salam hh\n");
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = ft_dbl_strlen(map) - 1;
	printf("len: %d\n", len);
	printf("seg hh\n");
	while (map[i])
	{
		j = 0;
		printf("%s\n", map[i]);
		while(map[i][j])
		{
			if (map[i][j] == 'D')
			{
				printf("len: %d i: %d\n", len, i);
				if (i == len || i == 0)
					return (1);
				printf("hhhhhhhhhhhhhhhhhhhhh\n");
				if (j == 0 || j == (ft_strlen(map[i]) - 1))
					return (1);
				if (!((map[i - 1][j] == '1' && map[i + 1][j] == '1')
				|| (map[i][j + 1] == '1' && map[i][j - 1] == '1')))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	door_pos(t_depot *depot)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (depot->map[i])
	{
		j = 0;
		while (depot->map[i][j])
		{
			if (depot->map[i][j] == 'D')
			{
				depot->door_x = j;
				depot->door_y = i;
			}
			j++;
		}
		i++;
	}
}
