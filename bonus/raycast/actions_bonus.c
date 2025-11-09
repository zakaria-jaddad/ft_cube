/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:02:43 by zajaddad          #+#    #+#             */
/*   Updated: 2025/11/09 03:07:17 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_bonus.h"

static bool	is_valid_move(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_y < 0 || new_y > (game->map_height)
		|| new_x > (int)(ft_strlen(game->depot->map[new_y])) - 1)
		return (false);
	if (game->depot->map[new_y][new_x] == '1' || game->depot->map[new_y][new_x] == 'D')
		return (false);
	return (true);
}

void	upsy(t_game *game, double y)
{
	double	new_y;

	new_y = (game->player->map_y + y);
	if (is_valid_move(game, game->player->map_x, new_y) == true)
	{
		game->player->map_y = new_y;
	}
}

void	upsx(t_game *game, double x)
{
	double	new_x;

	new_x = (game->player->map_x + x);
	if (is_valid_move(game, new_x, game->player->map_y) == true)
	{
		game->player->map_x = new_x;
	}
}
