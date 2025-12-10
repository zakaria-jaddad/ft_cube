/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:36:55 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/10 17:42:31 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_bonus.h"

static void	update_bobbing(t_game *game)
{
	float	sine_value;

	if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_W)
		|| mlx_is_key_down(game->mlx->mlx, MLX_KEY_A)
		|| mlx_is_key_down(game->mlx->mlx, MLX_KEY_D)
		|| mlx_is_key_down(game->mlx->mlx, MLX_KEY_S))
	{
		game->player->bobbing_val += BOB_SPEED * 5;
		sine_value = sin(game->player->bobbing_val);
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
	int			vs;
	uint32_t	y_screen;
	uint32_t	x;
	uint32_t	y_img;

	(void)!(vs = (int)game->player->bob_offset + 10, update_bobbing(game), x =
		-1);
	while (++x < game->player->pov->width)
	{
		y_img = 0;
		while (y_img < game->player->pov->height)
		{
			color = sample_texture_rgba(game->player->pov, x, y_img);
			if (color == 0)
			{
				y_img++;
				continue ;
			}
			y_screen = y_img + vs;
			if (y_screen < game->mlx->img->height)
				mlx_put_pixel(game->mlx->img, x, y_screen, color);
			y_img++;
		}
	}
}
