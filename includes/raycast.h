#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include "parsing.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define ROTATION_SPEED 0.10
# define PIXSIZE 20
# define MOVE_SPEED .17
# define SKY_COLOR 0xFFB1F2FF
# define FLOOR_COLOR 0x01E1EFF2
# define NUM_RAYS (int)(SCREEN_WIDTH / PIXSIZE)

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_mlx
{
	mlx_t			*mlx;
	mlx_image_t		*img;
}					t_mlx;

typedef enum e_direction
{
	NO,
	SO,
	WE,
	EA,
}					t_direction;

typedef struct s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct s_player
{
	t_vector		*direction;
	t_vector		*plane;
	double			map_x;
	double			map_y;
}					t_player;

typedef struct s_game
{
	t_player		*player;
	t_depot			*depot;
	t_mlx			*mlx;
	int				map_height;
}					t_game;

double				get_direction_x(t_direction direction);
double				get_direction_y(t_direction direction);
t_direction			get_direction(t_depot *depot);
t_player			*init_player(t_depot *depot);
void				free_player(t_player *player);
t_vector			*create_vector(double x, double y);
void				upsy(t_game *game, double y);
void				upsx(t_game *game, double x);
void				ft_cube(void *param);
bool				cub_raycast(t_depot *depot);
void				player_hook(void *param);
void				ft_hook(void *param);
t_mlx				*init_mlx(void);
void				free_mlx(t_mlx *mlx);

static inline void	rotate_player(t_player *player, double rotation_angle)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = player->direction->x;
	player->direction->x = player->direction->x * cos(rotation_angle)
		- player->direction->y * sin(rotation_angle);
	player->direction->y = oldDirX * sin(rotation_angle) + player->direction->y
		* cos(rotation_angle);
	oldPlaneX = player->plane->x;
	player->plane->x = player->plane->x * cos(rotation_angle) - player->plane->y
		* sin(rotation_angle);
	player->plane->y = oldPlaneX * sin(rotation_angle) + player->plane->y
		* cos(rotation_angle);
}

#endif // !RAYCASTING_H
