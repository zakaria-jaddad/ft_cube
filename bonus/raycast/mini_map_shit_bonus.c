/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_shit_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:16:09 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/13 13:46:03 by ilarhrib         ###   ########.fr       */
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

	px = mm->base_x + (10 / 2) - mm->shift_x;
	py = mm->base_y + (10 / 2) - mm->shift_y;
	x = 0;
	while (x < 10 - (10 / 3))
	{
		y = 0;
		while (y < 10 - (10 / 3))
		{
			if (px + x >= 0 && py + y >= 0
				&& px + x < SCREEN_WIDTH
				&& py + y < SCREEN_HEIGHT)
				mlx_put_pixel(game->mlx->img,
					px + x, py + y, 0xFFFFFFFF);
			y++;
		}
		x++;
	}
}

static void	draw_map_cell(t_game *game, t_minimap *mm,
		int i, int j)
{
	uint32_t	color;
	int			px;
	int			py;

	px = mm->base_x + (j - mm->cx) * PIXSIZE - mm->shift_x;
	py = mm->base_y + (i - mm->cy) * PIXSIZE - mm->shift_y;
	if (i >= 0 && j >= 0
		&& i < game->map_height
		&& j < (int)ft_strlen(game->depot->map[i]))
	{
		if (game->depot->map[i][j] != '1')
		{
			color = game->depot->f_color;
			draw_square(game, px, py, color);
		}
	}
}

static void	draw_map_view(t_game *game, t_minimap *mm)
{
	int	i;
	int	j;

	i = mm->cy - 4;
	while (i <= mm->cy + 10)
	{
		j = mm->cx - 4;
		while (j <= mm->cx + 10)
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
	mm.cx = (int)floor(game->player->map_x);
	mm.cy = (int)floor(game->player->map_y);
	mm.base_x = 8 + 2 * PIXSIZE;
	mm.base_y = 8 + 2 * PIXSIZE;
	mm.shift_x = (int)((game->player->map_x - mm.cx) * PIXSIZE);
	mm.shift_y = (int)((game->player->map_y - mm.cy) * PIXSIZE);
	draw_map_view(game, &mm);
	draw_player_at(game, &mm);
}
