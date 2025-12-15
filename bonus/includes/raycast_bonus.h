/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 16:00:52 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/14 23:00:03 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_BONUS_H
# define RAYCAST_BONUS_H

# include "../../lib/libft/libft.h"
# include "/mnt/homes/zajaddad/.local/lib/MLX42/include/MLX42/MLX42.h"
# include "parsing_bonus.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 800
# define ROTATION_ANGLE 0.09
# define PIXSIZE 20
# define MOVE_SPEED .10
# define POV_PATH "./bonus/textures/zlayji_pov.png"

# define BOB_AMPLITUDE 8.0f
# define BOB_SPEED 0.05f

typedef struct s_minimap
{
	int				cx;
	int				cy;
	int				base_x;
	int				base_y;
}					t_minimap;

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
	no,
	so,
	we,
	ea,
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
	mlx_texture_t	*pov;
	float			bobbing_val;
	float			bob_offset;
}					t_player;

typedef struct s_mouse
{
	bool			start_flag;
	double			last_x_pos;
}					t_mouse;

typedef struct s_game
{
	t_player		*player;
	t_depot			*depot;
	t_mlx			*mlx;
	t_mouse			mouse;
	int				map_height;
	mlx_texture_t	*tex_no;
	mlx_texture_t	*tex_so;
	mlx_texture_t	*tex_we;
	mlx_texture_t	*tex_ea;
	mlx_texture_t	*tex_dr;
}					t_game;

typedef struct s_algorithmique
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	double			side_dist_x;
	double			side_dist_y;
	int				side;
	double			perp_wall_dist;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
	int				line_height;
	double			walldist;
	int				wall_top;
	int				wall_bottom;
}					t_algorithmique;

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
void				cursor_hook(double x, double y, void *param);
t_mlx				*init_mlx(void);
void				free_mlx(t_mlx *mlx);
void				advance_ray(t_algorithmique *algo);
void				init_step_dist(t_game *game, t_algorithmique *algo);
void				init_delta_xy(t_algorithmique *algo);
void				init_xy(t_game *game, t_algorithmique *algo);
void				init_ray_dir(int x, t_game *game, t_algorithmique *algo);
void				render_minimap(t_game *game);
void				pov(t_game *game);

static inline void	rotate_player(t_player *player, double rotation_angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->direction->x;
	player->direction->x = player->direction->x * cos(rotation_angle)
		- player->direction->y * sin(rotation_angle);
	player->direction->y = old_dir_x * sin(rotation_angle)
		+ player->direction->y * cos(rotation_angle);
	old_plane_x = player->plane->x;
	player->plane->x = player->plane->x * cos(rotation_angle) - player->plane->y
		* sin(rotation_angle);
	player->plane->y = old_plane_x * sin(rotation_angle) + player->plane->y
		* cos(rotation_angle);
}

static inline bool	check_out_bound(t_game *game, t_algorithmique *algo)
{
	return (algo->map_x < 0 || algo->map_y < 0
		|| algo->map_y >= game->map_height
		|| algo->map_x >= (int)ft_strlen(game->depot->map[algo->map_y]));
}

//-----------------Textures---------------------//
int					sample_texture_rgba(mlx_texture_t *tex, int tx, int ty);
int					load_textures(t_game *g, t_depot *depot);
void				destroy_textures(t_game *g);
mlx_texture_t		*pick_tex(t_algorithmique *a, t_game *g);
void				cast_wall_textured(int x, t_game *game,
						t_algorithmique *algo, mlx_texture_t *tex);

#endif
