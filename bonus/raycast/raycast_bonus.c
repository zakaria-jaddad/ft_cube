/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:39:32 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/10 18:02:57 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_bonus.h"

void	open_doors(t_game *game)
{
	int		px;
	int		py;
	char	**map;

	px = game->player->map_x;
	py = game->player->map_y;
	map = game->depot->map;
	if (map[py - 1][px] == 'D')
		map[py - 1][px] = 'O';
	if (map[py + 1][px] == 'D')
		map[py + 1][px] = 'O';
	if (map[py][px - 1] == 'D')
		map[py][px - 1] = 'O';
	if (map[py][px + 1] == 'D')
		map[py][px + 1] = 'O';
}

void	close_doors(t_game *game)
{
	int		px;
	int		py;
	char	**map;

	px = game->player->map_x;
	py = game->player->map_y;
	map = game->depot->map;
	if (map[py - 1][px] == 'O')
		map[py - 1][px] = 'D';
	if (map[py + 1][px] == 'O')
		map[py + 1][px] = 'D';
	if (map[py][px - 1] == 'O')
		map[py][px - 1] = 'D';
	if (map[py][px + 1] == 'O')
		map[py][px + 1] = 'D';
}

void	door_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_O))
		open_doors(game);
	if (mlx_is_key_down(game->mlx->mlx, MLX_KEY_C))
		close_doors(game);
}

static void	init_more_info(t_game *game, t_depot *depot)
{
	game->depot = depot;
	game->mouse = (t_mouse){.last_x_pos = 0, .start_flag = true};
	game->map_height = 0;
	while (game->depot->map[game->map_height] != NULL)
		game->map_height++;
}

bool	cub_raycast(t_depot *depot)
{
	t_game	game;

	init_more_info(&game, depot);
	game.mlx = init_mlx();
	if (game.mlx == NULL)
		return (false);
	game.player = init_player(game.depot);
	if (game.player == NULL)
		return (free_mlx(game.mlx), false);
	mlx_set_mouse_pos(game.mlx->mlx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	if (load_textures(&game, depot))
	{
		free_player(game.player);
		free_mlx(game.mlx);
		destroy_textures(&game);
		return (false);
	}
	mlx_loop_hook(game.mlx->mlx, player_hook, &game);
	mlx_loop_hook(game.mlx->mlx, door_hook, &game);
	mlx_cursor_hook(game.mlx->mlx, cursor_hook, &game);
	mlx_loop_hook(game.mlx->mlx, ft_cube, &game);
	mlx_loop_hook(game.mlx->mlx, ft_hook, game.mlx);
	mlx_loop(game.mlx->mlx);
	mlx_terminate(game.mlx->mlx);
	return (free_player(game.player), true);
}
