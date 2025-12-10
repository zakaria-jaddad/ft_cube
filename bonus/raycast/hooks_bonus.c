/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:00:07 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/10 17:51:02 by zajaddad         ###   ########.fr       */
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
	if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(game->mlx->mlx, MLX_KEY_H))
		rotate_player(game->player, -ROTATION_SPEED);
	if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(game->mlx->mlx, MLX_KEY_L))
		rotate_player(game->player, ROTATION_SPEED);
}

void	cursor_hook(double x, double y, void *param)
{
	t_game	*game;
	int		sw;

	sw = SCREEN_WIDTH / 2;
	game = (t_game *)param;
	(void)y;
	if (game->mouse.start_flag == true)
	{
		game->mouse.last_x_pos = x;
		game->mouse.start_flag = false;
		return ;
	}
	if (x > game->mouse.last_x_pos)
		rotate_player(game->player, ROTATION_SPEED / 3);
	else if (x < game->mouse.last_x_pos)
		rotate_player(game->player, -ROTATION_SPEED / 3);
	mlx_set_mouse_pos(game->mlx->mlx, sw, SCREEN_HEIGHT / 2);
	game->mouse.last_x_pos = sw;
}
