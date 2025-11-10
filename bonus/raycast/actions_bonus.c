/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:02:43 by zajaddad          #+#    #+#             */
/*   Updated: 2025/11/10 10:42:05 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_bonus.h"

// TODO: REFACTOR THIS
static bool	is_valid_move(t_game *game, double nx, double ny)
{
	int tx;
	int ty;
	tx = (int)floor(nx);
	ty = (int)floor(ny);
	if (tx < 0 || ty < 0)
		return (false);
	if (ty >= game->map_height)
		return (false);
	if (tx >= (int)ft_strlen(game->depot->map[ty]))
		return (false);
	if (game->depot->map[ty][tx] == '1' || game->depot->map[ty][tx] == 'D')
		return (false);
	return (true);
}

void	upsy(t_game *game, double y)
{
	double	new_y;

	new_y = (game->player->map_y + y);
	if (is_valid_move(game, game->player->map_x + 0.0, new_y) == true)
	{
		game->player->map_y = new_y;
	}
}

void	upsx(t_game *game, double x)
{
	double	new_x;

	new_x = (game->player->map_x + x);
	if (is_valid_move(game, new_x, game->player->map_y + 0.0) == true)
	{
		game->player->map_x = new_x;
	}
}
