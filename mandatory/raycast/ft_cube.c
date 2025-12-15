/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:48:17 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/10 17:11:10 by zajaddad         ###   ########.fr       */
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
