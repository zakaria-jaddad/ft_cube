/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_wall_textured.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:55:07 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/10 17:41:59 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_bonus.h"

static int	pack_rgba(int r, int g, int b, int a)
{
	int	color;

	color = ((r << 24) | (g << 16) | (b << 8) | a);
	return (color);
}

int	sample_texture_rgba(mlx_texture_t *tex, int tx, int ty)
{
	size_t	idx;
	int		r;
	int		g;
	int		b;
	int		a;

	if (!tex || !tex->pixels || tex->bytes_per_pixel != 4)
		return (0x000000FF);
	if (tx < 0)
		tx = 0;
	if (ty < 0)
		ty = 0;
	if (tx >= (int)tex->width)
		tx = (int)tex->width - 1;
	if (ty >= (int)tex->height)
		ty = (int)tex->height - 1;
	idx = ((size_t)ty * tex->width + (size_t)tx) * 4;
	r = tex->pixels[idx + 0];
	g = tex->pixels[idx + 1];
	b = tex->pixels[idx + 2];
	a = tex->pixels[idx + 3];
	return (pack_rgba(r, g, b, a));
}

static void	draw_tex_line(int x, mlx_texture_t *tex, t_algorithmique *algo,
		t_game *game)
{
	uint32_t	color;
	int			tex_y;
	int			y;

	y = algo->wall_top;
	while (y <= algo->wall_bottom)
	{
		tex_y = (int)algo->tex_pos;
		algo->tex_pos += algo->step;
		color = sample_texture_rgba(tex, algo->tex_x, tex_y);
		if (x >= 0 && x < SCREEN_WIDTH)
			mlx_put_pixel(game->mlx->img, x, y, color);
		++y;
	}
}

void	cast_wall_textured(int x, t_game *game, t_algorithmique *algo,
		mlx_texture_t *tex)
{
	if (tex == NULL)
		return ;
	if (algo->side == 0)
		algo->wall_x = game->player->map_y + algo->walldist * algo->ray_dir_y;
	else
		algo->wall_x = game->player->map_x + algo->walldist * algo->ray_dir_x;
	algo->wall_x -= floor(algo->wall_x);
	algo->tex_x = (int)(algo->wall_x * (double)tex->width);
	if ((algo->side == 0 && algo->ray_dir_x > 0) || (algo->side == 1
			&& algo->ray_dir_y < 0))
		algo->tex_x = (int)tex->width - algo->tex_x - 1;
	if (algo->tex_x < 0)
		algo->tex_x = 0;
	if (algo->tex_x >= (int)tex->width)
		algo->tex_x = (int)tex->width - 1;
	algo->step = (double)tex->height / (double)algo->line_height;
	algo->tex_pos = (algo->wall_top - SCREEN_HEIGHT / 2.0 + algo->line_height
			/ 2.0) * algo->step;
	draw_tex_line(x, tex, algo, game);
}
