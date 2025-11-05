/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:00:52 by zajaddad          #+#    #+#             */
/*   Updated: 2025/11/05 06:53:44 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
#define RAYCAST_H

#include "../../lib/MLX42/include/MLX42/MLX42.h"
#include "../../lib/libft/libft.h"
#include "parsing.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800
#define ROTATION_SPEED 0.05
#define PIXSIZE 20
#define MOVE_SPEED .10
#define SKY_COLOR 0x00FFFF
#define FLOOR_COLOR 0x000000

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
  t_vector *direction;
  t_vector *plane;
  double map_x;
  double map_y;
} t_player;

typedef struct s_game {
  t_player *player;
  t_depot *depot;
  t_mlx *mlx;
  int map_height;
  mlx_texture_t *tex_no; // chamal alkhawa
  mlx_texture_t *tex_so; // janob okda
  mlx_texture_t *tex_we; // lgharb ajmi
  mlx_texture_t *tex_ea; // char9 o lbar9
} t_game;

typedef struct s_algorithmique {
  double camera_x;
  double ray_dir_x;
  double ray_dir_y;
  int map_x;
  int map_y;
  double delta_dist_x;
  double delta_dist_y;
  int step_x;
  int step_y;
  double side_dist_x;
  double side_dist_y;
  int side;
  double perp_wall_dist;
  double wall_x;
  int tex_x;
  double step;
  double tex_pos;
  int line_height;
  double walldist;
  int wall_top;
  int wall_bottom;
} t_algorithmique;

double get_direction_x(t_direction direction);
double get_direction_y(t_direction direction);
t_direction get_direction(t_depot *depot);
t_player *init_player(t_depot *depot);
void free_player(t_player *player);
t_vector *create_vector(double x, double y);
void upsy(t_game *game, double y);
void upsx(t_game *game, double x);
void ft_cube(void *param);
bool cub_raycast(t_depot *depot);
void player_hook(void *param);
void ft_hook(void *param);
t_mlx *init_mlx(void);
void free_mlx(t_mlx *mlx);
void advance_ray(t_algorithmique *algo);
void init_step_dist(t_game *game, t_algorithmique *algo);
void init_delta_xy(t_algorithmique *algo);
void init_xy(t_game *game, t_algorithmique *algo);
void init_ray_dir(int x, t_game *game, t_algorithmique *algo);

// TODO: LEARN ABOUT THIS
static inline void rotate_player(t_player *player, double rotation_angle) {
  double old_dir_x;
  double old_plane_x;

  old_dir_x = player->direction->x;
  player->direction->x = player->direction->x * cos(rotation_angle) -
                         player->direction->y * sin(rotation_angle);
  player->direction->y = old_dir_x * sin(rotation_angle) +
                         player->direction->y * cos(rotation_angle);
  old_plane_x = player->plane->x;
  player->plane->x = player->plane->x * cos(rotation_angle) -
                     player->plane->y * sin(rotation_angle);
  player->plane->y = old_plane_x * sin(rotation_angle) +
                     player->plane->y * cos(rotation_angle);
}

static inline bool check_out_bound(t_game *game, t_algorithmique *algo) {
  return (algo->map_x < 0 || algo->map_y < 0 ||
          algo->map_y >= game->map_height ||
          algo->map_x >= (int)ft_strlen(game->depot->map[algo->map_y]));
}

static inline uint32_t pack_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  return ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) |
         (uint32_t)a;
}

static inline uint32_t shade_rgba(uint32_t color, double factor) {
  uint8_t r = (color >> 24) & 0xFF;
  uint8_t g = (color >> 16) & 0xFF;
  uint8_t b = (color >> 8) & 0xFF;
  uint8_t a = (color >> 0) & 0xFF;

  r = (uint8_t)fmin(255.0, r * factor);
  g = (uint8_t)fmin(255.0, g * factor);
  b = (uint8_t)fmin(255.0, b * factor);

  return pack_rgba(r, g, b, a);
}

static inline uint32_t sample_texture_rgba(mlx_texture_t *tex, int tx, int ty) {
  if (!tex || !tex->pixels || tex->bytes_per_pixel != 4)
    return 0x000000FF;
  if (tx < 0)
    tx = 0;
  if (ty < 0)
    ty = 0;
  if (tx >= (int)tex->width)
    tx = (int)tex->width - 1;
  if (ty >= (int)tex->height)
    ty = (int)tex->height - 1;

  size_t idx = ((size_t)ty * tex->width + (size_t)tx) * 4;
  uint8_t r = tex->pixels[idx + 0];
  uint8_t g = tex->pixels[idx + 1];
  uint8_t b = tex->pixels[idx + 2];
  uint8_t a = tex->pixels[idx + 3];
  return pack_rgba(r, g, b, a);
}

//-----------------Textures---------------------//

int load_textures(t_game *g, char *no, char *so, char *we, char *ea);
void destroy_textures(t_game *g);
mlx_texture_t *pick_tex(t_algorithmique *a, t_game *g);

#endif
