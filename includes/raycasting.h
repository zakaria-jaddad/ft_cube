/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 05:11:33 by zajaddad          #+#    #+#             */
/*   Updated: 2025/08/01 08:24:31 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// NO = (-1, 0)
// SO = (1, 0)
// WE = (0, -1)
// EA = (0, 1)

#ifndef RAYCASTING_H
#define RAYCASTING_H

//#include "../MLX42/include/MLX42/MLX42.h"
#include "../libft/libft.h"
#include "parsing.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

bool cub_raycast(t_depot *depot);

typedef struct s_img {
  void *img;
  char *addr;
  int bits_per_pixel;
  int line_length;
  int endian;
} t_img;

typedef struct s_mlx {
  mlx_t *mlx;
  mlx_image_t *img;
} t_mlx;

typedef enum e_direction {
  NO,
  SO,
  WE,
  EA,
} t_direction;

typedef struct s_vector {
  double x;
  double y;
} t_vector;

typedef struct s_player {
  t_vector *position;
  t_vector *direction; // the direction vector stores value that ditermine
                       // player current direction
  t_vector *plane;
  double map_x;
  double map_y;
  char letter;
} t_player;

typedef struct s_game {
  t_player *player;
  t_depot *depot;
  t_mlx *mlx;
} t_game;

static inline char get_player_letter(t_direction direction) {
  if (direction == NO)
    return 'N';
  else if (direction == SO)
    return 'S';
  else if (direction == WE)
    return 'W';
  else
    return 'E';
}

#define PIXSIZE 20
static inline void mini_map(void *param) {
  t_game *game = (t_game *)param;
  char **map = game->depot->map;
  uint32_t color;

  for (int i = 0; map[i] != NULL; i++) {
    for (int j = 0; map[i][j] != 0; j++) {
      int pixel_x = j * PIXSIZE;
      int pixel_y = i * PIXSIZE;
      if (map[i][j] == '1')
        color = 0xFFFD77AC;
      else if (map[i][j] == ' ')
        continue;
      else
        color = 0xFF123456;
      if (i == (int)game->player->map_y && j == (int)game->player->map_x)
        color = 0xFFEDCBA9;
      for (int x = 0; x < PIXSIZE; x++) {
        for (int y = 0; y < PIXSIZE; y++) {
          if (pixel_x + x < 800 && pixel_y + y < 600) {
            mlx_put_pixel(game->mlx->img, pixel_x + x, pixel_y + y, color);
          }
        }
      }
    }
  }
}

static inline void ft_hook(void *param) {

  t_mlx *mlx = (t_mlx *)param;

  if (mlx_is_key_down(mlx->mlx, MLX_KEY_ESCAPE) ||
      mlx_is_key_down(mlx->mlx, MLX_KEY_Q))
    mlx_close_window(mlx->mlx);
  if (mlx_is_key_down(mlx->mlx, MLX_KEY_UP))
    mlx->img->instances[0].y -= 5;
  if (mlx_is_key_down(mlx->mlx, MLX_KEY_DOWN))
    mlx->img->instances[0].y += 5;
  if (mlx_is_key_down(mlx->mlx, MLX_KEY_LEFT))
    mlx->img->instances[0].x -= 5;
  if (mlx_is_key_down(mlx->mlx, MLX_KEY_RIGHT))
    mlx->img->instances[0].x += 5;
}

static inline void mini_map_player_hook(void *param) {

  t_game *game = (t_game *)param;

  if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_W)) {
    game->player->map_y -= .2;
  }
  if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_A)) {
    game->player->map_x -= .2;
  }
  if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_S)) {
    game->player->map_y += .2;
  }
  if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_D)) {
    game->player->map_x += .2;
  }
}

#endif // !RAYCASTING_H
