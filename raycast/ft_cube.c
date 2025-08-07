/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:48:17 by zajaddad          #+#    #+#             */
/*   Updated: 2025/08/07 16:03:54 by zajaddad         ###   ########.fr       */
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

static void	cast_wall_escaping_norms(int x, int wall_top, int wall_bottom,
		t_game *game)
{
	int	tx;
	int	y;

	tx = 0;
	while (tx < PIXSIZE)
	{
		y = wall_top;
		if (x + tx >= 0 && x + tx < SCREEN_WIDTH)
			while (y <= wall_bottom)
				mlx_put_pixel(game->mlx->img, x + tx, y++, 0xFF202020);
		tx++;
	}
}

static void	cast_wall(int x, t_game *game, t_algorithmique *algo)
{
	double	walldist;
	int		line_height;
	int		wall_top;
	int		wall_bottom;

	if (algo->side == 0)
		walldist = (algo->map_x - game->player->map_x + (1 - algo->step_x) / 2)
			/ algo->ray_dir_x;
	else
		walldist = (algo->map_y - game->player->map_y + (1 - algo->step_y) / 2)
			/ algo->ray_dir_y;
	line_height = (int)(SCREEN_HEIGHT / walldist);
	wall_top = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (wall_top < 0)
		wall_top = 0;
	wall_bottom = line_height / 2 + SCREEN_HEIGHT / 2;
	if (wall_bottom >= SCREEN_HEIGHT)
		wall_bottom = SCREEN_HEIGHT - 1;
	cast_wall_escaping_norms(x, wall_top, wall_bottom, game);
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
		x += 3;
	}
}
