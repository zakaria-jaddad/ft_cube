/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:48:17 by zajaddad          #+#    #+#             */
/*   Updated: 2025/11/10 08:55:24 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

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

static void	draw_tex_line(int x, mlx_texture_t *tex, t_algorithmique *algo,
		t_game *game)
{
	uint32_t	color;
	int			tex_y;
	int			y;

	y = algo->wall_top;
	while (y <= algo->wall_bottom)
	{
		tex_y = (int)algo->tex_pos;
		algo->tex_pos += algo->step;
		color = sample_texture_rgba(tex, algo->tex_x, tex_y);
		if (algo->side == 1)
			color = shade_rgba(color, 0.75);
		if (x >= 0 && x < SCREEN_WIDTH)
			mlx_put_pixel(game->mlx->img, x, y, color);
		++y;
	}
}

static void	cast_wall_textured(int x, t_game *game, t_algorithmique *algo)
{
	mlx_texture_t	*tex;

	if (algo->side == 0)
		algo->wall_x = game->player->map_y + algo->walldist * algo->ray_dir_y;
	else
		algo->wall_x = game->player->map_x + algo->walldist * algo->ray_dir_x;
	algo->wall_x -= floor(algo->wall_x);
	tex = pick_tex(algo, game);
	if (!tex)
		return ;
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
	draw_tex_line(x, tex, algo, game);
}

static void	cast_wall(int x, t_game *game, t_algorithmique *algo)
{
	double	walldist;
	int		line_height;
	int		wall_top;
	int		wall_bottom;

	if (algo->side == 0)
		walldist = (algo->map_x - game->player->map_x + (1 - algo->step_x)
				/ 2.0) / algo->ray_dir_x;
	else
		walldist = (algo->map_y - game->player->map_y + (1 - algo->step_y)
				/ 2.0) / algo->ray_dir_y;
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
	(void)!(algo->line_height = line_height, algo->walldist = walldist, 1);
	(void)!(algo->wall_top = wall_top, algo->wall_bottom = wall_bottom, 1);
	cast_wall_textured(x, game, algo);
}

void	ft_cube(void *param)
{
	t_game			*game;
	t_algorithmique	algo;
	int				x;

	(void)!(x = 0, game = (t_game *)param);
	draw_sky_floor(game);
	while (x < SCREEN_WIDTH)
	{
		init_ray_dir(x, game, &algo);
		init_xy(game, &algo);
		init_delta_xy(&algo);
		init_step_dist(game, &algo);
		while (true)
		{
			advance_ray(&algo);
			if (check_out_bound(game, &algo))
				break ;
			if (game->depot->map[algo.map_y][algo.map_x] == '1')
			{
				cast_wall(x, game, &algo);
				break ;
			}
		}
		x++;
	}
}
