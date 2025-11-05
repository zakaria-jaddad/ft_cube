/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:00:07 by zajaddad          #+#    #+#             */
/*   Updated: 2025/08/06 17:11:10 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_bonus.h"

void	ft_hook(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (mlx_is_key_down(mlx->mlx, MLX_KEY_ESCAPE) || mlx_is_key_down(mlx->mlx,
			MLX_KEY_Q))
		mlx_close_window(mlx->mlx);
}

void	player_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_W))
		(void)(upsx(game, game->player->direction->x * MOVE_SPEED), upsy(game,
				game->player->direction->y * MOVE_SPEED));
	if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_A))
		(void)(upsx(game, -game->player->plane->x * MOVE_SPEED), upsy(game,
				-game->player->plane->y * MOVE_SPEED));
	if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_S))
	{
		upsx(game, -game->player->direction->x * MOVE_SPEED);
		upsy(game, -game->player->direction->y * MOVE_SPEED);
	}
	if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_D))
	{
		upsx(game, game->player->plane->x * MOVE_SPEED);
		upsy(game, game->player->plane->y * MOVE_SPEED);
	}
	if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_LEFT))
		rotate_player(game->player, -ROTATION_SPEED);
	if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_RIGHT))
		rotate_player(game->player, ROTATION_SPEED);
}
