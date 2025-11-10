/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:00:07 by zajaddad          #+#    #+#             */
/*   Updated: 2025/11/10 08:38:14 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"
#include <stdlib.h>

void	free_game(t_game *game)
{
	if (game == NULL)
		return ;
	free_player(game->player);
	free_depot(game->depot);
	if (game->tex_no)
		mlx_delete_texture(game->tex_no);
	if (game->tex_so)
		mlx_delete_texture(game->tex_so);
	if (game->tex_we)
		mlx_delete_texture(game->tex_we);
	if (game->tex_ea)
		mlx_delete_texture(game->tex_ea);
	exit(EXIT_SUCCESS);
}

void	ft_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_ESCAPE)
		|| mlx_is_key_down(game->mlx->mlx, MLX_KEY_Q))
	{
		free_game(game);
		mlx_close_window(game->mlx->mlx);
	}
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
	if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(game->mlx->mlx, MLX_KEY_H))
		rotate_player(game->player, -ROTATION_SPEED);
	if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(game->mlx->mlx, MLX_KEY_L))
		rotate_player(game->player, ROTATION_SPEED);
}
