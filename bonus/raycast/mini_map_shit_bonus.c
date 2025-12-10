/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_shit_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:16:09 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/10 17:50:25 by zajaddad         ###   ########.fr       */
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

static void	draw_player_at(t_game *game, int base_x, int base_y, int shift_x,
		int shift_y)
{
	int	px;
	int	py;
	int	x;
	int	y;

	px = base_x + (10 / 2) - shift_x;
	py = base_y + (10 / 2) - shift_y;
	x = 0;
	while (x < 10 - (10 / 3))
	{
		y = 0;
		while (y < 10 - (10 / 3))
		{
			if (px + x >= 0 && py + y >= 0 && px + x < SCREEN_WIDTH && py
				+ y < SCREEN_HEIGHT)
				mlx_put_pixel(game->mlx->img, px + x, py + y, 0xFFFFFFFF);
			y++;
		}
		x++;
	}
}

static void	draw_map_view(t_game *game, int cx, int cy, int base_x, int base_y,
		int shift_x, int shift_y)
{
	uint32_t	color;
	int			i;
	int			j;
	int			px;
	int			py;

	i = cy - 4;
	while (i <= cy + 10)
	{
		j = cx - 4;
		while (j <= cx + 10)
		{
			px = base_x + (j - cx) * PIXSIZE - shift_x;
			py = base_y + (i - cy) * PIXSIZE - shift_y;
			if (i >= 0 && j >= 0 && i < game->map_height
				&& j < (int)ft_strlen(game->depot->map[i]))
				if (game->depot->map[i][j] != '1')
				{
					color = game->depot->f_color;
					draw_square(game, px, py, color);
				}
			j++;
		}
		i++;
	}
}

/* external wrapper used by main rendering loop */
void	render_minimap(t_game *game)
{
	int	cx;
	int	cy;
	int	base_x;
	int	base_y;
	int	shift_x;
	int	shift_y;

	if (!game || !game->depot)
		return ;
	cx = (int)floor(game->player->map_x);
	cy = (int)floor(game->player->map_y);
	base_x = 8 + 2 * PIXSIZE; /* left origin for center cell */
	base_y = 8 + 2 * PIXSIZE;
	shift_x = (int)((game->player->map_x - cx) * PIXSIZE);
	shift_y = (int)((game->player->map_y - cy) * PIXSIZE);
	draw_map_view(game, cx, cy, base_x, base_y, shift_x, shift_y);
	draw_player_at(game, base_x, base_y, shift_x, shift_y);
}
