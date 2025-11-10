#include "../includes/parsing.h"

int is_closed_by_walls(char **map) {
  int x;
  int y;

  x = 0;
  while (map[x]) {
    y = 0;
    while (map[x][y]) {
      if (map[x][y] == '0' || !not_player_point(map[x][y])) {
        //	if (y > (int)ft_strlen(map[x + 1]))
        //	{
        //		ft_fprintf(2, "!Map Invalid\n");
        //		return (1);
        //	}
        if (map[x - 1][y] != '1' && map[x - 1][y] != '0' &&
            not_player_point(map[x - 1][y])) {
          ft_fprintf(2, "!Map Invalid\n");
          return (1);
        }
        if (map[x + 1][y] != '1' && map[x + 1][y] != '0' &&
            not_player_point(map[x + 1][y])) {
          ft_fprintf(2, "!Map Invalid\n");
          return (1);
        }
        if (map[x][y + 1] != '1' && map[x][y + 1] != '0' &&
            not_player_point(map[x][y + 1])) {
          ft_fprintf(2, "!Map Invalid\n");
          return (1);
        }
        if (map[x][y - 1] != '1' && map[x][y - 1] != '0' &&
            not_player_point(map[x][y - 1])) {
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

int not_player_point(char c) {
  if (c != 'N' && c != 'S' && c != 'W' && c != 'E')
    return (1);
  return (0);
}

int retrieve_player_pos(t_depot *depot) {
  int i;
  int j;

  i = 0;
  while (depot->map[i]) {
    j = 0;
    while (depot->map[i][j]) {
      if (!not_player_point(depot->map[i][j])) {
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

uint32_t rgb_convert(int r, int g, int b) {
  // MLX42 expects 0xRRGGBBAA
  return ((uint32_t)(r & 0xFF) << 24) | ((uint32_t)(g & 0xFF) << 16) |
         ((uint32_t)(b & 0xFF) << 8) | 0xFFu; // alpha = 255
}

uint32_t rgba_convert(int r, int g, int b, int a) {
  // 0xRRGGBBAA
  return ((uint32_t)(r & 0xFF) << 24) | ((uint32_t)(g & 0xFF) << 16) |
         ((uint32_t)(b & 0xFF) << 8) | ((uint32_t)(a & 0xFF));
}

int clean_path(t_depot *depot) {
  depot->path_to_NO = ft_strtrim(depot->path_to_NO, "\n\t\r");
  depot->path_to_SO = ft_strtrim(depot->path_to_SO, "\n\t\r");
  depot->path_to_WE = ft_strtrim(depot->path_to_WE, "\n\t\r");
  depot->path_to_EA = ft_strtrim(depot->path_to_EA, "\n\t\r");
  if (!depot->path_to_EA || !depot->path_to_NO || !depot->path_to_SO ||
      !depot->path_to_WE)
    return (1);
  return (0);
}
