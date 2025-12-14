/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_shit_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:16:09 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/14 22:59:50 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_bonus.h"

static void	draw_square(t_game *game, int px, int py, uint32_t color)
{
	int	x;
	int	y;

	x = 0;
	while (x < PIXSIZE)
	{
		y = 0;
		while (y < PIXSIZE)
		{
			if (px + x >= 0 && py + y >= 0 && px + x < SCREEN_WIDTH && py
				+ y < SCREEN_HEIGHT)
			{
				mlx_put_pixel(game->mlx->img, px + x, py + y, color);
			}
			y++;
		}
		x++;
	}
}

static void	draw_player_at(t_game *game, t_minimap *mm)
{
	int	px;
	int	py;
	int	x;
	int	y;

	px = mm->base_x + (10 / 2);
	py = mm->base_y + (10 / 2);
	x = 0;
	while (x < 6)
	{
		y = 0;
		while (y < 6)
		{
			mlx_put_pixel(game->mlx->img, px + x, py + y, 0xFFFFFFFF);
			y++;
		}
		x++;
	}
}

static void	draw_map_cell(t_game *game, t_minimap *mm, int i, int j)
{
	int	px;
	int	py;

	px = mm->base_x + (j - mm->cx) * (PIXSIZE / 2);
	py = mm->base_y + (i - mm->cy) * (PIXSIZE / 2);
	if (i >= 0 && j >= 0 && i < game->map_height
		&& j < (int)ft_strlen(game->depot->map[i]))
	{
		if (game->depot->map[i][j] != '1')
		{
			draw_square(game, px, py, 0x000000FF);
		}
	}
}

static void	draw_map_view(t_game *game, t_minimap *mm)
{
	int	i;
	int	j;

	i = mm->cy - 20;
	while (i <= mm->cy + 20)
	{
		j = mm->cx - 20;
		while (j <= mm->cx + 20)
		{
			draw_map_cell(game, mm, i, j);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_game *game)
{
	t_minimap	mm;

	if (!game || !game->depot || !game->player)
		return ;
	mm.cx = (int)(game->player->map_x);
	mm.cy = (int)(game->player->map_y);
	mm.base_x = 2 * PIXSIZE;
	mm.base_y = 2 * PIXSIZE;
	draw_map_view(game, &mm);
	draw_player_at(game, &mm);
}
