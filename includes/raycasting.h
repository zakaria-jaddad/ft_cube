/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 05:11:33 by zajaddad          #+#    #+#             */
/*   Updated: 2025/08/01 10:58:50 by zajaddad         ###   ########.fr       */
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
#include <stdlib.h>

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

static void draw_player(t_game *game) {
  int mid = PIXSIZE / 2;
  int pixel_x = (int)game->player->map_x * PIXSIZE;
  int pixel_y = (int)game->player->map_y * PIXSIZE;

  for (int y = 0; y <= mid; y++) {
    for (int j = 0; j < mid - y; j++)
      ;
    for (int x = 0; x < (2 * y + 1); x++) {
      if (pixel_x + (mid - y) + x < 800 && pixel_y + y < 600) {
        mlx_put_pixel(game->mlx->img, pixel_x + (mid - y) + x, pixel_y + y,
                      0xFFFFFFFF);
      }
    }
  }

  for (int y = mid - 1; y >= 0; y--) {
    for (int j = 0; j < mid - y; j++)
      ;
    for (int x = 0; x < (2 * y + 1); x++) {
      if (pixel_x + (mid - y) + x < 800 && pixel_y + (mid + y) < 600) {
        mlx_put_pixel(game->mlx->img, pixel_x + (mid - y) + x,
                      pixel_y + (mid + y), 0xFFFFFFFF);
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
  if (mlx_is_key_down(mlx->mlx, MLX_KEY_UP))
    mlx->img->instances[0].y -= 5;
  if (mlx_is_key_down(mlx->mlx, MLX_KEY_DOWN))
    mlx->img->instances[0].y += 5;
  if (mlx_is_key_down(mlx->mlx, MLX_KEY_LEFT))
    mlx->img->instances[0].x -= 5;
  if (mlx_is_key_down(mlx->mlx, MLX_KEY_RIGHT))
    mlx->img->instances[0].x += 5;
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

static inline void mini_map_player_hook(void *param) {

  t_game *game = (t_game *)param;
  int x;
  int y;

  if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_K)) {
    y = game->player->map_y - .2;
    if (valid_y(game->map_height, y) == true)
      game->player->map_y -= .2;
  }
  if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_H)) {
    x = game->player->map_x - .2;
    if (valid_x(ft_strlen(game->depot->map[(int)game->player->map_y]), x) ==
        true)
      game->player->map_x -= .2;
  }
  if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_J)) {
    y = game->player->map_y + .2;
    if (valid_y(game->map_height, y) == true)
      game->player->map_y += .2;
  }
  if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_L)) {
    x = game->player->map_x + .2;
    if (valid_x(ft_strlen(game->depot->map[(int)game->player->map_y]), x) ==
        true)
      game->player->map_x += .2;
  }
}

#endif // !RAYCASTING_H
