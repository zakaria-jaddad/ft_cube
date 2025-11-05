/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:39:32 by zajaddad          #+#    #+#             */
/*   Updated: 2025/11/05 06:28:08 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_bonus.h"

bool	cub_raycast(t_depot *depot)
{
	t_game	game;

	game.depot = depot;
	game.mouse = (t_mouse){.last_x_pos = 0, .start_flag = true};
	game.mlx = init_mlx();
	if (game.mlx == NULL)
		return (false);
	game.player = init_player(game.depot);
	if (game.player == NULL)
		return (free_mlx(game.mlx), false);
	game.map_height = 0;
	while (game.depot->map[game.map_height] != NULL)
		game.map_height++;
	if (load_textures(&game, depot))
	{
		free_player(game.player);
		free_mlx(game.mlx);
		destroy_textures(&game);
		printf("1\n");
		return (false);
	}
	mlx_loop_hook(game.mlx->mlx, player_hook, &game);
	mlx_cursor_hook(game.mlx->mlx, cursor_hook, &game);
	mlx_loop_hook(game.mlx->mlx, ft_cube, &game);
	mlx_loop_hook(game.mlx->mlx, ft_hook, game.mlx);
	mlx_loop(game.mlx->mlx);
	mlx_terminate(game.mlx->mlx);
	free_player(game.player);
	return (true);
}
