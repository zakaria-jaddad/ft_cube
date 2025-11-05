/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:00:58 by zajaddad          #+#    #+#             */
/*   Updated: 2025/08/07 15:02:42 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_bonus.h"

void	init_ray_dir(int x, t_game *game, t_algorithmique *algo)
{
	algo->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	algo->ray_dir_x = game->player->direction->x + game->player->plane->x
		* algo->camera_x;
	algo->ray_dir_y = game->player->direction->y + game->player->plane->y
		* algo->camera_x;
	if (algo->ray_dir_x == 0)
		algo->ray_dir_x = 1e-30;
	if (algo->ray_dir_y == 0)
		algo->ray_dir_y = 1e-30;
}

void	init_xy(t_game *game, t_algorithmique *algo)
{
	algo->map_x = (int)game->player->map_x;
	algo->map_y = (int)game->player->map_y;
}

void	init_delta_xy(t_algorithmique *algo)
{
	algo->delta_dist_x = fabs(1 / algo->ray_dir_x);
	algo->delta_dist_y = fabs(1 / algo->ray_dir_y);
}

void	init_step_dist(t_game *game, t_algorithmique *algo)
{
	if (algo->ray_dir_x < 0)
	{
		algo->step_x = -1;
		algo->side_dist_x = (game->player->map_x - algo->map_x)
			* algo->delta_dist_x;
	}
	else
	{
		algo->step_x = 1;
		algo->side_dist_x = (algo->map_x + 1.0 - game->player->map_x)
			* algo->delta_dist_x;
	}
	if (algo->ray_dir_y < 0)
	{
		algo->step_y = -1;
		algo->side_dist_y = (game->player->map_y - algo->map_y)
			* algo->delta_dist_y;
	}
	else
	{
		algo->step_y = 1;
		algo->side_dist_y = (algo->map_y + 1.0 - game->player->map_y)
			* algo->delta_dist_y;
	}
}

void	advance_ray(t_algorithmique *algo)
{
	if (algo->side_dist_x < algo->side_dist_y)
	{
		algo->side_dist_x += algo->delta_dist_x;
		algo->map_x += algo->step_x;
		algo->side = 0;
	}
	else
	{
		algo->side_dist_y += algo->delta_dist_y;
		algo->map_y += algo->step_y;
		algo->side = 1;
	}
}
