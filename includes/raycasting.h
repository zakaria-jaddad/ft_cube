/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 05:11:33 by zajaddad          #+#    #+#             */
/*   Updated: 2025/08/02 12:16:40 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// NO = (-1, 0)
// SO = (1, 0)
// WE = (0, -1)
// EA = (0, 1)

#ifndef RAYCASTING_H
#define RAYCASTING_H

#include "../MLX42/include/MLX42/MLX42.h"
#include "../libft/libft.h"
#include "parsing.h"
#include <math.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define RSPEED 0.04

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
  int map_height;
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

#include <math.h>

#define PIXSIZE 20 // Size of each pixel

static void draw_player(t_game *game) {
  int mid = PIXSIZE / 2;
  int pixel_x = (int)game->player->map_x * PIXSIZE;
  int pixel_y = (int)game->player->map_y * PIXSIZE;

  double angle = atan2(game->player->direction->y, game->player->direction->x);

  // Draw a filled triangle pointing upwards (before rotation)
  // Height of the triangle = PIXSIZE, base = PIXSIZE
  for (int y = 0; y < PIXSIZE; y++) {
    // Calculate base width at this y (linearly decreasing)
    int base_width = (PIXSIZE - y) * 2 - 1;
    int start_x = mid - base_width / 2;

    for (int x = 0; x < base_width; x++) {
      // Rotate the point around the center (mid, mid)
      int local_x = start_x + x;
      int local_y = y;

      int rotated_x =
          (int)((local_x - mid) * cos(angle) - (local_y - mid) * sin(angle));
      int rotated_y =
          (int)((local_x - mid) * sin(angle) + (local_y - mid) * cos(angle));

      int draw_x = pixel_x + mid + rotated_x;
      int draw_y = pixel_y + mid + rotated_y;

      if (draw_x >= 0 && draw_x < 800 && draw_y >= 0 && draw_y < 600) {
        mlx_put_pixel(game->mlx->img, draw_x, draw_y, 0xFFFFFFFF);
      }
    }
  }
}

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
      for (int x = 0; x < PIXSIZE; x++) {
        for (int y = 0; y < PIXSIZE; y++) {
          if (pixel_x + x < 800 && pixel_y + y < 600) {
            mlx_put_pixel(game->mlx->img, pixel_x + x, pixel_y + y, color);
          }
        }
      }
    }
  }
  draw_player(game);
}

static inline void ft_hook(void *param) {

  t_mlx *mlx = (t_mlx *)param;

  if (mlx_is_key_down(mlx->mlx, MLX_KEY_ESCAPE) ||
      mlx_is_key_down(mlx->mlx, MLX_KEY_Q))
    mlx_close_window(mlx->mlx);
}

static inline bool valid_y(int map_height, double map_y) {

  if (map_y >= 0 && (int)map_y < map_height) {
    return true;
  }
  return false;
}

static inline bool valid_x(int line_width, double map_x) {
  if (map_x >= 0 && (int)map_x < line_width) {
    return true;
  }
  return false;
}

static inline void rotate_player(t_player *player, double rotation_angle) {
  double oldDirX = player->direction->x;
  player->direction->x = player->direction->x * cos(rotation_angle) -
                         player->direction->y * sin(rotation_angle);
  player->direction->y = oldDirX * sin(rotation_angle) +
                         player->direction->y * cos(rotation_angle);
  double oldPlaneX = player->plane->x;
  player->plane->x = player->plane->x * cos(rotation_angle) -
                     player->plane->y * sin(rotation_angle);
  player->plane->y =
      oldPlaneX * sin(rotation_angle) + player->plane->y * cos(rotation_angle);
}

static inline void mini_map_player_hook(void *param) {

  t_game *game = (t_game *)param;
  int x;
  int y;

  if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_W)) {
    y = game->player->map_y - .5;
    if (valid_y(game->map_height, y) == true)
      game->player->map_y -= .5;
  }
  if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_A)) {
    x = game->player->map_x - .5;
    if (valid_x(ft_strlen(game->depot->map[(int)game->player->map_y]), x) ==
        true)
      game->player->map_x -= .5;
  }
  if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_S)) {
    y = game->player->map_y + .5;
    if (valid_y(game->map_height, y) == true)
      game->player->map_y += .5;
  }
  if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_D)) {
    x = game->player->map_x + .5;
    if (valid_x(ft_strlen(game->depot->map[(int)game->player->map_y]), x) ==
        true)
      game->player->map_x += .5;
  }
  if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_LEFT)) {
    rotate_player(game->player, -RSPEED);
  }
  if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_RIGHT)) {
    rotate_player(game->player, RSPEED);
  }
}

#endif // !RAYCASTING_H
