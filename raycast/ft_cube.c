/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:48:17 by zajaddad          #+#    #+#             */
/*   Updated: 2025/08/06 17:18:36 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

static void	draw_sky_floor(t_game *game)
{
	int	mid;

	mid = floor((double)SCREEN_HEIGHT / 2);
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = 0; j < mid; j++)
		{
			mlx_put_pixel(game->mlx->img, i, j, game->depot->c_color);
		}
	}
	for (int i = 0; i < SCREEN_WIDTH; i++)
	{
		for (int j = mid; j < SCREEN_HEIGHT; j++)
		{
			mlx_put_pixel(game->mlx->img, i, j, game->depot->f_color);
		}
	}
}

// Norms a jexmi
void	ft_cube(void *param)
{
	t_game	*game;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		side;
	double	walldist;
	int		line_height;
	int		wall_top;
	int		wall_bottom;
	int		tail_size;
	int		draw_x;

	game = (t_game *)param;
	draw_sky_floor(game);
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		ray_dir_x = game->player->direction->x + game->player->plane->x
			* camera_x;
		ray_dir_y = game->player->direction->y + game->player->plane->y
			* camera_x;
		if (ray_dir_x == 0)
			ray_dir_x = 1e-30;
		if (ray_dir_y == 0)
			ray_dir_y = 1e-30;
		map_x = (int)game->player->map_x;
		map_y = (int)game->player->map_y;
		delta_dist_x = fabs(1 / ray_dir_x);
		delta_dist_y = fabs(1 / ray_dir_y);
		int step_x, step_y;
		double side_dist_x, side_dist_y;
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (game->player->map_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - game->player->map_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (game->player->map_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - game->player->map_y) * delta_dist_y;
		}
		while (true)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (map_x < 0 || map_y < 0 || map_y >= game->map_height
				|| map_x >= (int)ft_strlen(game->depot->map[map_y]))
				break ;
			if (game->depot->map[map_y][map_x] == '1')
			{
				if (side == 0)
					walldist = (map_x - game->player->map_x + (1 - step_x) / 2)
						/ ray_dir_x;
				else
					walldist = (map_y - game->player->map_y + (1 - step_y) / 2)
						/ ray_dir_y;
				line_height = (int)(SCREEN_HEIGHT / walldist);
				wall_top = -line_height / 2 + SCREEN_HEIGHT / 2;
				if (wall_top < 0)
					wall_top = 0;
				wall_bottom = line_height / 2 + SCREEN_HEIGHT / 2;
				if (wall_bottom >= SCREEN_HEIGHT)
					wall_bottom = SCREEN_HEIGHT - 1;
				tail_size = PIXSIZE;
				for (int tx = 0; tx < tail_size; tx++)
				{
					draw_x = x + tx;
					if (draw_x >= 0 && draw_x < SCREEN_WIDTH)
					{
						for (int y = wall_top; y <= wall_bottom; y++)
						{
							mlx_put_pixel(game->mlx->img, draw_x, y,
								0xFF202020);
						}
					}
				}
				break ;
			}
		}
	}
}
