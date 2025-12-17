/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:48:17 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/10 17:42:09 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_bonus.h"

static void	draw_sky_floor(t_game *game)
{
	int				mid;
	int				i;
	int				j;
	double			angle;
	int				x_offset;
	int				src_x;
	int				src_y;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;
	uint32_t		color;

	(void)!(mid = floor((double)SCREEN_HEIGHT / 2), i = 0);
	angle = atan2(game->player->direction->y, game->player->direction->x);
	if (angle < 0)
		angle += 2.0 * M_PI;
	x_offset = (int)((angle / (M_PI)) * game->sky->width) % game->sky->width;
	for (int y = 0; y < (SCREEN_HEIGHT / 2); ++y)
	{
		if (y >= (int)game->sky->height)
			continue ;
		for (int x = 0; x < SCREEN_WIDTH; ++x)
		{
			src_x = (x + x_offset) % game->sky->width;
			src_y = y;
			i = (src_y * game->sky->width + src_x) * game->sky->bytes_per_pixel;
			r = game->sky->pixels[i + 0];
			g = game->sky->pixels[i + 1];
			b = game->sky->pixels[i + 2];
			a = game->sky->pixels[i + 3];
			color = (r << 24) | (g << 16) | (b << 8) | (a);
			mlx_put_pixel(game->mlx->img, x, y, color);
		}
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

static mlx_texture_t	*get_tex(t_game *game, t_algorithmique *algo)
{
	if (game->depot->map[algo->map_y][algo->map_x] == '1')
		return (pick_tex(algo, game));
	else
		return (game->tex_dr);
}

static void	cast_wall(int x, t_game *game, t_algorithmique *algo)
{
	double	walldist;
	int		line_height;
	int		wall_top;
	int		wall_bottom;
	double	veclen;

	veclen = sqrt(algo->ray_dir_x * algo->ray_dir_x + algo->ray_dir_y
			* algo->ray_dir_y);
	if (algo->side == 0)
		walldist = algo->side_dist_x - algo->delta_dist_x;
	else
		walldist = algo->side_dist_y - algo->delta_dist_y;
	if (walldist < 1e-6)
		walldist = 1e-6;
	walldist = walldist / veclen;
	line_height = (int)(SCREEN_HEIGHT / walldist);
	wall_top = (SCREEN_HEIGHT / 2) - (line_height / 2);
	if (wall_top < 0)
		wall_top = 0;
	wall_bottom = line_height / 2 + SCREEN_HEIGHT / 2;
	if (wall_bottom >= SCREEN_HEIGHT)
		wall_bottom = SCREEN_HEIGHT - 1;
	(void)!(algo->line_height = line_height, algo->walldist = walldist, 1);
	(void)!(algo->wall_top = wall_top, algo->wall_bottom = wall_bottom, 1);
	cast_wall_textured(x, game, algo, get_tex(game, algo));
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
	(void)!(pov(game), render_minimap(game), 0);
}
