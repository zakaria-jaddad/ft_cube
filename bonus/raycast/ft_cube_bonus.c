/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:48:17 by zajaddad          #+#    #+#             */
/*   Updated: 2025/11/09 07:26:10 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_bonus.h"
#include <stdint.h>
#include <stdio.h>

static void	draw_sky_floor(t_game *game)
{
	int	mid;
	int	i;
	int	j;

	(void)!(mid = floor((double)SCREEN_HEIGHT / 2), i = 0);
	while (i < SCREEN_WIDTH)
	{
		j = 0;
		while (j < mid)
			mlx_put_pixel(game->mlx->img, i, j++, game->depot->c_color);
		i++;
	}
	i = 0;
	while (i < SCREEN_WIDTH)
	{
		j = mid;
		while (j < SCREEN_HEIGHT)
			mlx_put_pixel(game->mlx->img, i, j++, game->depot->f_color);
		i++;
	}
}

void	cast_wall_textured(int x, t_game *game, t_algorithmique *algo,
		mlx_texture_t *tex)
{
	int			tex_y;
	uint32_t	color;

	if (!tex)
		return ;
	if (algo->side == 0)
		algo->wall_x = game->player->map_y + algo->walldist * algo->ray_dir_y;
	else
		algo->wall_x = game->player->map_x + algo->walldist * algo->ray_dir_x;
	algo->wall_x -= floor(algo->wall_x);
	algo->tex_x = (int)(algo->wall_x * (double)tex->width);
	if ((algo->side == 0 && algo->ray_dir_x > 0) || (algo->side == 1
			&& algo->ray_dir_y < 0))
		algo->tex_x = (int)tex->width - algo->tex_x - 1;
	if (algo->tex_x < 0)
		algo->tex_x = 0;
	if (algo->tex_x >= (int)tex->width)
		algo->tex_x = (int)tex->width - 1;
	algo->step = (double)tex->height / (double)algo->line_height;
	algo->tex_pos = (algo->wall_top - SCREEN_HEIGHT / 2.0 + algo->line_height
			/ 2.0) * algo->step;
	for (int y = algo->wall_top; y <= algo->wall_bottom; ++y)
	{
		tex_y = (int)algo->tex_pos;
		algo->tex_pos += algo->step;
		color = sample_texture_rgba(tex, algo->tex_x, tex_y);
		if (algo->side == 1)
			color = shade_rgba(color, 0.75);
		if (x >= 0 && x < SCREEN_WIDTH)
			mlx_put_pixel(game->mlx->img, x, y, color);
	}
}
bool	check_cast_type(char cast_type)
{
	if (cast_type == '1')
		return (false);
	else
		return (true);
}

static void	cast_wall(int x, t_game *game, t_algorithmique *algo)
{
	double	walldist;
	int		line_height;
	int		wall_top;
	int		wall_bottom;
	bool	is_door_cast;
	double veclen = sqrt(algo->ray_dir_x * algo->ray_dir_x + algo->ray_dir_y * algo->ray_dir_y);

	is_door_cast = check_cast_type(game->depot->map[algo->map_y][algo->map_x]);
	if (algo->side == 0)
		walldist = algo->side_dist_x - algo->delta_dist_x;
	else 
		walldist = algo->side_dist_y -  algo->delta_dist_y;
	
	if (walldist < 1e-6)
		walldist = 1e-6;

	walldist = walldist / veclen;

	algo->perp_wall_dist = walldist;
	line_height = (int)(SCREEN_HEIGHT / walldist);
	wall_top =  (SCREEN_HEIGHT / 2) - (line_height / 2);
	if (wall_top < 0)
		wall_top = 0;
	wall_bottom = line_height / 2 + SCREEN_HEIGHT / 2;
	if (wall_bottom >= SCREEN_HEIGHT)
		wall_bottom = SCREEN_HEIGHT - 1;
	(void)!(algo->line_height = line_height, algo->walldist = walldist, 1);
	(void)!(algo->wall_top = wall_top, algo->wall_bottom = wall_bottom, 1);
	if (is_door_cast == false)
		cast_wall_textured(x, game, algo, pick_tex(algo, game));
	else
	{
		cast_wall_textured(x, game, algo, game->tex_dr);
	}
}

void	update_bobbing(t_game *game)
{
	if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_W) || 
    mlx_is_key_down(game->mlx->mlx, MLX_KEY_A) || 
    mlx_is_key_down(game->mlx->mlx, MLX_KEY_D) || 
    mlx_is_key_down(game->mlx->mlx, MLX_KEY_S)
    )
	{
		game->player->bobbing_val += BOB_SPEED * 5; 
		float sine_value = sin(game->player->bobbing_val);
		game->player->bob_offset = sine_value * BOB_AMPLITUDE;
	}
	else
	{
		game->player->bob_offset = 0.0f;
		game->player->bobbing_val = 0.0f;
	}
}

void	pov(t_game *game)
{
	uint32_t	color;
	int			vertical_shift = (int)game->player->bob_offset + 10; 

	for (uint32_t x = 0; x < game->player->pov->width; x++)
	{
		for (uint32_t y_img = 0; y_img < game->player->pov->height; y_img++)
		{
			color = sample_texture_rgba(game->player->pov, x, y_img);
			if (color == 0)
				continue ;
			uint32_t y_screen = y_img + vertical_shift; 
			if (y_screen < game->mlx->img->height)
			{
			    mlx_put_pixel(game->mlx->img, x, y_screen, color);
			}
		}
	}
}

void	ft_cube(void *param)
{
	t_game			*game;
	t_algorithmique	algo;
	int				x;

	(void)!(x = 0, game = (t_game *)param, draw_sky_floor(game), 0);
	while (x < SCREEN_WIDTH)
	{
		(void)!(init_ray_dir(x, game, &algo), init_xy(game, &algo),
			init_delta_xy(&algo), init_step_dist(game, &algo), 0);
		while (true)
		{
			advance_ray(&algo);
			if (check_out_bound(game, &algo))
				break ;
			if (game->depot->map[algo.map_y][algo.map_x] == '1'
				|| game->depot->map[algo.map_y][algo.map_x] == 'D')
			{
				cast_wall(x, game, &algo);
				break ;
			}
		}
		x++;
	}
	update_bobbing(game);
	pov(game);
	render_minimap(game);
}
