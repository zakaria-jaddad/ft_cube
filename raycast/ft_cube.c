/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:48:17 by zajaddad          #+#    #+#             */
/*   Updated: 2025/08/07 16:03:54 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

// Draw a PIXSIZE-wide textured vertical slice for this wall hit.
static void cast_wall_textured(int x, int draw_start, int draw_end,
                               int line_height, t_game *game,
                               t_algorithmique *algo, double walldist, int wall_top)
{
    mlx_texture_t   *tex;
    double          wall_x;
    int             tex_x;
    double          step;
    double          tex_pos;
    int             tx;
    int             y;

    // 1) Which texture face? (uses your existing function)
    tex = pick_tex(algo, game);
    if (!tex)
        return;

    // 2) Where exactly did the ray hit along that face? (fraction 0..1)
    if (algo->side == 0)
        wall_x = game->player->map_y + walldist * algo->ray_dir_y; // vertical wall -> use Y
    else
        wall_x = game->player->map_x + walldist * algo->ray_dir_x; // horizontal wall -> use X
    wall_x -= floor(wall_x);

    // 3) Convert to texture X column
    tex_x = (int)(wall_x * (double)tex->width);

    // Flip so the image isn’t mirrored for certain faces (classic Wolf3D behavior)
    if (algo->side == 0 && algo->ray_dir_x > 0)
        tex_x = (int)tex->width - tex_x - 1;
    if (algo->side == 1 && algo->ray_dir_y < 0)
        tex_x = (int)tex->width - tex_x - 1;

    // 4) Vertical scaling: how much to move in the texture for each screen pixel
    step = (double)tex->height / (double)line_height;

    // Calculate the starting texture row using the unclamped wall_top
    // This ensures correct texture mapping even when the wall extends above the screen
    tex_pos = (wall_top - SCREEN_HEIGHT / 2 + line_height / 2) * step;
    // If wall_top was negative (wall extends above screen), advance to first visible pixel
    if (wall_top < 0)
        tex_pos += (-wall_top) * step;

    // 5) Draw a slice of width PIXSIZE (your loop steps x+=PIXSIZE in ft_cube)
    tx = 0;
    while (tx < PIXSIZE)
    {
        int x_screen = x + tx;
        double tpos  = tex_pos; // reset per column so all PIXSIZE columns match

        if (x_screen >= 0 && x_screen < SCREEN_WIDTH)
        {
            y = draw_start;
            while (y <= draw_end)
            {
                int tex_y = (int)tpos;
                if (tex_y < 0) tex_y = 0;
                if (tex_y >= (int)tex->height) tex_y = (int)tex->height - 1;

                uint32_t color = get_tex_pixel(tex, tex_x, tex_y);
                mlx_put_pixel(game->mlx->img, x_screen, y, color);

                tpos += step;
                y++;
            }
        }
        tx++;
    }
}

static void	draw_sky_floor(t_game *game)
{
	int	mid;
	int	i;
	int	j;

	(void)!(mid = floor((double)SCREEN_HEIGHT / 2), i = 0);
	while (i < SCREEN_WIDTH)
	{
		j = 0;
		while (j < mid)
			mlx_put_pixel(game->mlx->img, i, j++, game->depot->c_color);
		i++;
	}
	i = 0;
	while (i < SCREEN_WIDTH)
	{
		j = mid;
		while (j < SCREEN_HEIGHT)
			mlx_put_pixel(game->mlx->img, i, j++, game->depot->f_color);
		i++;
	}
}

// static void	cast_wall_escaping_norms(int x, int wall_top, int wall_bottom,
// 		t_game *game)
// {
// 	int	tx;
// 	int	y;

// 	tx = 0;
// 	while (tx < PIXSIZE)
// 	{
// 		y = wall_top;
// 		if (x + tx >= 0 && x + tx < SCREEN_WIDTH)
// 			while (y <= wall_bottom)
// 				mlx_put_pixel(game->mlx->img, x + tx, y++, 0xFF202020);
// 		tx++;
// 	}
// }

static void	cast_wall(int x, t_game *game, t_algorithmique *algo)
{
	double	walldist;
	int		line_height;
	int		wall_top;
	int		wall_bottom;
	int		draw_start;
	int		draw_end;

	if (algo->side == 0)
		walldist = (algo->map_x - game->player->map_x + (1 - algo->step_x) / 2)
			/ algo->ray_dir_x;
	else
		walldist = (algo->map_y - game->player->map_y + (1 - algo->step_y) / 2)
			/ algo->ray_dir_y;
	line_height = (int)(SCREEN_HEIGHT / walldist);
	wall_top = -line_height / 2 + SCREEN_HEIGHT / 2;
	wall_bottom = line_height / 2 + SCREEN_HEIGHT / 2;
	draw_start = wall_top;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = wall_bottom;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	// cast_wall_escaping_norms(x, draw_start, draw_end, game);
	cast_wall_textured(x, draw_start, draw_end, line_height, game, algo, walldist, wall_top);
}

void	ft_cube(void *param)
{
	t_game			*game;
	t_algorithmique	algo;
	int				x;

	(void)!(x = 0, game = (t_game *)param);
	draw_sky_floor(game);
	while (x < SCREEN_WIDTH)
	{
		init_ray_dir(x, game, &algo);
		init_xy(game, &algo);
		init_delta_xy(&algo);
		init_step_dist(game, &algo);
		while (true)
		{
			advance_ray(&algo);
			if (check_out_bound(game, &algo))
				break ;
			if (game->depot->map[algo.map_y][algo.map_x] == '1')
			{
				cast_wall(x, game, &algo);
				break ;
			}
		}
		x += 3;
	}
}
