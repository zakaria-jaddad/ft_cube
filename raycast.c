/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 06:55:05 by zajaddad          #+#    #+#             */
/*   Updated: 2025/08/01 12:57:40 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/raycasting.h"

double get_direction_x(t_direction direction);
double get_direction_y(t_direction direction);
t_direction get_direction(t_depot *depot);
void init_plane(double *px, double *py, double dx, double dy);

t_vector *create_vector(double x, double y) {
  t_vector *v;

  v = malloc(sizeof(t_vector));
  if (v == NULL)
    return (NULL);
  v->x = x;
  v->y = y;
  return (v);
}

t_player *create_player(void) {
  t_player *p;

  p = malloc(sizeof(t_player));
  if (p == NULL)
    return (NULL);
  ft_bzero(p, sizeof(t_player));
  return (p);
}

void set_player_cor(double *x, double *y, char **map, t_direction d) {
  int i;
  int j;
  char player;

  i = 0;
  j = 0;
  player = get_player_letter(d);
  while (map[i]) {
    j = 0;
    while (map[i][j]) {
      if (map[i][j] == player)
        return (void)!(*x = j, *y = i);
      j++;
    }
    i++;
  }
}

t_player *init_player(t_depot *depot) {
  t_direction d;
  t_player *p;

  d = get_direction(depot);
  p = create_player();
  if (p == NULL)
    return (NULL);
  p->direction = create_vector(get_direction_x(d), get_direction_y(d));
  if (p->direction == NULL)
    return (/* free_player */ NULL);

  // set current player map position
  set_player_cor(&p->map_x, &p->map_y, depot->map, d);

  // init player position
  p->position = create_vector(p->map_x * ((double)SCREEN_WIDTH / 1000),
                              p->map_y * ((double)SCREEN_HEIGHT / 1000));
  if (p->position == NULL)
    return (/* free_player */ NULL);
  p->plane = create_vector(0, 0);
  if (p->position == NULL)
    return (/* free_player */ NULL);

  // plane initilazation
  // plane vector has one of a 4 values based on the direction vector
  init_plane(&p->plane->x, &p->plane->x, p->direction->x, p->direction->y);

  // player letter based on direction
  p->letter = get_player_letter(d);

  printf("p->direction->x = %f\n", p->direction->x);
  printf("p->direction->y = %f\n", p->direction->y);

  printf("p->map_x = %f\n", p->map_x);
  printf("p->map_y = %f\n", p->map_y);

  printf("p->map_x * ((double)SCREEN_WIDTH / 1000) = %f\n",
         p->map_x * ((double)SCREEN_WIDTH / 1000));
  printf("p->map_y * ((double)SCREEN_HEIGHT / 1000) = %f\n",
         p->map_y * ((double)SCREEN_HEIGHT / 1000));
  printf("p->plane->x = %f\n", p->plane->x);
  printf("p->plane->y = %f\n", p->plane->y);
  printf("p->letter = %c\n", p->letter);
  return (p);
}

t_mlx *init_mlx(void) {

  t_mlx *mlx = malloc(sizeof(t_mlx));
  if (mlx == NULL)
    return NULL;
  ft_bzero(mlx, sizeof(t_mlx));
  mlx->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "ft_cube", true);
  if (mlx->mlx == NULL)
    return (free(mlx), NULL);

  mlx->img = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
  if (mlx->img == NULL) {
    mlx_close_window(mlx->mlx);
    return (free(mlx), NULL);
  }
  if (mlx_image_to_window(mlx->mlx, mlx->img, 0, 0) == -1) {
    mlx_close_window(mlx->mlx);
    return (free(mlx), NULL);
  }
  return mlx;
}

bool cub_raycast(t_depot *depot) {
  t_game game;

  game.depot = depot;
  game.mlx = init_mlx();
  if (game.mlx == NULL)
    return (false);
  game.player = init_player(game.depot);
  if (game.player == NULL)
    return (false);
  for (game.map_height = 0; game.depot->map[game.map_height] != 0;
       game.map_height++)
    ;

  mlx_loop_hook(game.mlx->mlx, mini_map_player_hook, &game);
  mlx_loop_hook(game.mlx->mlx, mini_map, &game);
  mlx_loop_hook(game.mlx->mlx, ft_hook, game.mlx);

  mlx_loop(game.mlx->mlx);
  mlx_terminate(game.mlx->mlx);
  return (true);
}

double get_direction_x(t_direction direction) {
  if (direction == NO)
    return (-1);
  if (direction == SO)
    return (1);
  if (direction == WE)
    return (0);
  else
    return (0);
}

double get_direction_y(t_direction direction) {
  if (direction == NO)
    return (0);
  if (direction == SO)
    return (0);
  if (direction == WE)
    return (-1);
  else
    return (1);
}

t_direction get_direction(t_depot *depot) {
  if (depot->NO == 1)
    return (NO);
  if (depot->SO == 1)
    return (SO);
  if (depot->WE == 1)
    return (WE);
  else
    return EA;
}

void init_plane(double *px, double *py, double dx, double dy) {
  if (dx == 0 && dy == -1) {
    *px = 0.66;
    *py = 0;
  } else if (dx == 0 && dy == 1) {
    *px = -0.66;
    *py = 0;
  } else if (dx == 1 && dy == 0) {
    *px = 0;
    *py = 0.66;
  } else if (dx == -1 && dy == 0) {
    *px = 0;
    *py = -0.66;
  } else {
    *px = 0;
    *py = 0;
  }
}

