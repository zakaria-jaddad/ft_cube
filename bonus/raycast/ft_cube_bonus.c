/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:48:17 by zajaddad          #+#    #+#             */
/*   Updated: 2025/10/31 22:16:58 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_bonus.h"
#include <string.h>

static void draw_sky_floor(t_game *game) {
  int mid;
  int i;
  int j;

  (void)!(mid = floor((double)SCREEN_HEIGHT / 2), i = 0);
  while (i < SCREEN_WIDTH) {
    j = 0;
    while (j < mid)
      mlx_put_pixel(game->mlx->img, i, j++, game->depot->c_color);
    i++;
  }
  i = 0;
  while (i < SCREEN_WIDTH) {
    j = mid;
    while (j < SCREEN_HEIGHT)
      mlx_put_pixel(game->mlx->img, i, j++, game->depot->f_color);
    i++;
  }
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

// Choose texture by wall orientation and ray direction.
// Convention (common in Cub3D):
// - side == 0: vertical wall (E/W). ray_dir_x > 0 -> WE, else EA
// - side == 1: horizontal wall (N/S). ray_dir_y > 0 -> NO, else SO
void cast_wall_textured(int x, t_game *game, t_algorithmique *algo) {
  mlx_texture_t *tex;

  // Calculate line height on screen

  // Find where on the wall the ray hits (0..1) to get the texture X coordinate
  if (algo->side == 0)
    algo->wall_x = game->player->map_y + algo->walldist * algo->ray_dir_y;
  else
    algo->wall_x = game->player->map_x + algo->walldist * algo->ray_dir_x;
  algo->wall_x -= floor(algo->wall_x);

  // Pick the wall texture (NO/SO/WE/EA)
  tex = pick_tex(algo, game);
  if (!tex) {
    return;
  }

  // Texture X coordinate (flip to keep orientation consistent)
  algo->tex_x = (int)(algo->wall_x * (double)tex->width);
  if ((algo->side == 0 && algo->ray_dir_x > 0) ||
      (algo->side == 1 && algo->ray_dir_y < 0))
    algo->tex_x = (int)tex->width - algo->tex_x - 1;
  if (algo->tex_x < 0)
    algo->tex_x = 0;
  if (algo->tex_x >= (int)tex->width)
    algo->tex_x = (int)tex->width - 1;

  // How much to step in the texture for each screen pixel
  algo->step = (double)tex->height / (double)algo->line_height;
  // Starting texture y position
  algo->tex_pos =
      (algo->wall_top - SCREEN_HEIGHT / 2.0 + algo->line_height / 2.0) *
      algo->step;


  for (int y = algo->wall_top; y <= algo->wall_bottom; ++y) {
    int tex_y = (int)algo->tex_pos;
    algo->tex_pos += algo->step;
    uint32_t color = sample_texture_rgba(tex, algo->tex_x, tex_y);
    if (algo->side == 1)
      color = shade_rgba(color, 0.75);
    if (x >= 0 && x < SCREEN_WIDTH)
      mlx_put_pixel(game->mlx->img, x, y, color);
  }
}

/* static void cast_wall_escaping_norms(int x, int wall_top, int wall_bottom, */
/*                                      t_game *game) { */
/*   int tx; */
/*   int y; */
/**/
/*   tx = 0; */
/*   while (tx < PIXSIZE) { */
/*     y = wall_top; */
/*     if (x + tx >= 0 && x + tx < SCREEN_WIDTH) */
/*       while (y <= wall_bottom) */
/*         mlx_put_pixel(game->mlx->img, x + tx, y++, 0xFF202020); */
/*     tx++; */
/*   } */
/* } */

static void cast_wall(int x, t_game *game, t_algorithmique *algo) {
  double walldist;
  int line_height;
  int wall_top;
  int wall_bottom;

  // Compute perpendicular wall distance (avoid fisheye)
  if (algo->side == 0)
    walldist = (algo->map_x - game->player->map_x + (1 - algo->step_x) / 2.0) /
               algo->ray_dir_x;
  else
    walldist = (algo->map_y - game->player->map_y + (1 - algo->step_y) / 2.0) /
               algo->ray_dir_y;

  if (walldist < 1e-6)
    walldist = 1e-6;
  algo->perp_wall_dist = walldist;

  line_height = (int)(SCREEN_HEIGHT / walldist);
  wall_top = -line_height / 2 + SCREEN_HEIGHT / 2;
  if (wall_top < 0)
    wall_top = 0;
  wall_bottom = line_height / 2 + SCREEN_HEIGHT / 2;
  if (wall_bottom >= SCREEN_HEIGHT)
    wall_bottom = SCREEN_HEIGHT - 1;
  algo->line_height = line_height;
  algo->walldist = walldist;
  algo->wall_top = wall_top;
  algo->wall_bottom = wall_bottom;
  /* cast_wall_escaping_norms(x, wall_top, wall_bottom, game); */
  cast_wall_textured(x, game, algo);
}

void ft_cube(void *param) {
  t_game *game;
  t_algorithmique algo;
  int x;

  (void)!(x = 0, game = (t_game *)param);
  draw_sky_floor(game);
  while (x < SCREEN_WIDTH) {
    init_ray_dir(x, game, &algo);
    init_xy(game, &algo);
    init_delta_xy(&algo);
    init_step_dist(game, &algo);
    while (true) {
      advance_ray(&algo);
      if (check_out_bound(game, &algo))
        break;
      if (game->depot->map[algo.map_y][algo.map_x] == '1') {
        cast_wall(x, game, &algo);
        break;
      }
    }
    x++; // instead of this
    // x += PIXSIZE;
  }
}
