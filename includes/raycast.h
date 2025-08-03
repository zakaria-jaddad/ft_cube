
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
#define PIXSIZE 20
#define MOVE_SPEED .17
#define SKY_COLOR 0xFFB1F2FF
#define FLOOR_COLOR 0x01E1EFF2

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

// static void draw_player(t_game *game) {
//
//   int pixel_x = floor((game->player->map_x * PIXSIZE) - (int)(PIXSIZE / 2));
//   int pixel_y = floor((game->player->map_y * PIXSIZE) - (int)(PIXSIZE / 2));
//
//   for (int x = 0; x < PIXSIZE - (PIXSIZE / 3); x++) {
//     for (int y = 0; y < PIXSIZE - (PIXSIZE / 3); y++) {
//       // int draw_x = pixel_x + (int)(x * game->player->direction->x -
//       //                              y * game->player->direction->y);
//       // int draw_y = pixel_y + (int)(x * game->player->direction->y +
//       //                              y * game->player->direction->x);
//       if ((pixel_x + x < 800 && pixel_y + y < 600) &&
//           (pixel_x + x >= 0 && pixel_y + y >= 0)) {
//         mlx_put_pixel(game->mlx->img, pixel_x + x, pixel_y + y, 0xFFFFFFFF);
//       }
//     }
//   }
// }

// static inline void mini_map(void *param) {
//   t_game *game = (t_game *)param;
//   char **map = game->depot->map;
//   uint32_t color;
//
//   for (int i = 0; map[i] != NULL; i++) {
//     for (int j = 0; map[i][j] != 0; j++) {
//
//       int pixel_x = j * PIXSIZE;
//       int pixel_y = i * PIXSIZE;
//       if (map[i][j] == '1')
//         color = 0xFFFD77AC;
//       else if (map[i][j] == ' ') {
//         j++;
//         continue;
//       } else
//         color = 0xFF123456;
//       for (int x = 0; x < PIXSIZE; x++) {
//         for (int y = 0; y < PIXSIZE; y++) {
//           if (pixel_x + x < 800 && pixel_y + y < 600) {
//             mlx_put_pixel(game->mlx->img, pixel_x + x, pixel_y + y, color);
//           }
//         }
//       }
//     }
//   }
//   draw_player(game);
// }

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

static inline bool is_valid_move(t_game *game, int new_x, int new_y) {
  if (new_x < 0 || new_y < 0 || new_y > (game->map_height) ||
      new_x > (int)(ft_strlen(game->depot->map[new_y]))-1)
    return (false);
  if (game->depot->map[new_y][new_x] == '1')
    return (false);
  return (true);
}

static inline void update_player_pos_y(t_game *game, double y) {

  double new_y;

  new_y = (game->player->map_y + y);
  if (is_valid_move(game, game->player->map_x, new_y) == true) {
    game->player->map_y = new_y;
  }
}

static inline void update_player_pos_x(t_game *game, double x) {

  double new_x;

  new_x = (game->player->map_x + x);
  if (is_valid_move(game, new_x, game->player->map_y) == true) {
    game->player->map_x = new_x;
  }
}

static inline void mini_map_player_hook(void *param) {

  t_game *game = (t_game *)param;

  if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_W)) {
    update_player_pos_y(game, -MOVE_SPEED);
  }
  if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_A)) {
    update_player_pos_x(game, -MOVE_SPEED);
  }
  if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_S)) {
    update_player_pos_y(game, +MOVE_SPEED);
  }
  if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_D)) {
    update_player_pos_x(game, +MOVE_SPEED);
  }
  if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_LEFT)) {
    rotate_player(game->player, -RSPEED);
  }
  if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_RIGHT)) {
    rotate_player(game->player, RSPEED);
  }
}

static inline void draw_sky(mlx_image_t *img) {

  int mid = floor(SCREEN_HEIGHT / 2);

  for (int i = 0; i < SCREEN_WIDTH; i++) {
    for (int j = 0; j < mid; j++) {
      mlx_put_pixel(img, i, j, FLOOR_COLOR);
    }
  }

  for (int i = 0; i < SCREEN_WIDTH; i++) {
    for (int j = mid; j < SCREEN_HEIGHT; j++) {
      mlx_put_pixel(img, i, j, SKY_COLOR);
    }
  }
}
#endif // !RAYCASTING_H
