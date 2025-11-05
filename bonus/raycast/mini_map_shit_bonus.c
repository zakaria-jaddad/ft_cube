/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_shit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:16:09 by zajaddad          #+#    #+#             */
/*   Updated: 2025/08/07 16:00:29 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_bonus.h"

/* void	draw_player(t_game *game) */
/* { */
/* 	int	pixel_x; */
/* 	int	pixel_y; */
/**/
/* 	pixel_x = floor((game->player->map_x * PIXSIZE) - (int)(PIXSIZE / 2)); */
/* 	pixel_y = floor((game->player->map_y * PIXSIZE) - (int)(PIXSIZE / 2)); */
/* 	for (int x = 0; x < PIXSIZE - (PIXSIZE / 3); x++) */
/* 	{ */
/* 		for (int y = 0; y < PIXSIZE - (PIXSIZE / 3); y++) */
/* 		{ */
/* 			if ((pixel_x + x < 800 && pixel_y + y < 600) && (pixel_x + x >= 0 */
/* 					&& pixel_y + y >= 0)) */
/* 			{ */
/* 				mlx_put_pixel(game->mlx->img, pixel_x + x, pixel_y + y, */
/* 					0xFFFFFFFF); */
/* 			} */
/* 		} */
/* 	} */
/* } */
/**/
/* inline void	mini_map(void *param) */
/* { */
/* 	t_game		*game; */
/* 	char		**map; */
/* 	uint32_t	color; */
/* 	int			pixel_x; */
/* 	int			pixel_y; */
/**/
/* 	game = (t_game *)param; */
/* 	map = game->depot->map; */
/* 	for (int i = 0; map[i] != NULL; i++) */
/* 	{ */
/* 		for (int j = 0; map[i][j] != 0; j++) */
/* 		{ */
/* 			pixel_x = j * PIXSIZE; */
/* 			pixel_y = i * PIXSIZE; */
/* 			if (map[i][j] == '1') */
/* 				color = 0xFFFD77AC; */
/* 			else if (map[i][j] == ' ') */
/* 			{ */
/* 				j++; */
/* 				continue ; */
/* 			} */
/* 			else */
/* 				color = 0xFF123456; */
/* 			for (int x = 0; x < PIXSIZE; x++) */
/* 			{ */
/* 				for (int y = 0; y < PIXSIZE; y++) */
/* 				{ */
/* 					if (pixel_x + x < 800 && pixel_y + y < 600) */
/* 					{ */
/* 						mlx_put_pix
 *  						el(game->mlx->img, pixel_x + x, pixel_y + y, */
/* 							color); */
/* 					} */
/* 				} */
/* 			} */
/* 		} */
/* 	} */
/* 	draw_player(game); */
/* } */
