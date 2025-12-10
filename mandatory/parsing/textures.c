/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigrav <antigrav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:00:00 by antigrav          #+#    #+#             */
/*   Updated: 2025/12/08 17:00:00 by antigrav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube.h"
#include <stdio.h>

void	destroy_textures(t_game *g)
{
	if (g->tex_no)
		mlx_delete_texture(g->tex_no);
	if (g->tex_so)
		mlx_delete_texture(g->tex_so);
	if (g->tex_we)
		mlx_delete_texture(g->tex_we);
	if (g->tex_ea)
		mlx_delete_texture(g->tex_ea);
	g->tex_no = NULL;
	g->tex_so = NULL;
	g->tex_we = NULL;
	g->tex_ea = NULL;
}

int	load_textures(t_game *g)
{
	g->tex_no = mlx_load_png(g->depot->path_to_no);
	g->tex_so = mlx_load_png(g->depot->path_to_so);
	g->tex_we = mlx_load_png(g->depot->path_to_we);
	g->tex_ea = mlx_load_png(g->depot->path_to_ea);
	if (!g->tex_no || !g->tex_so || !g->tex_we || !g->tex_ea)
	{
		ft_fprintf(2, "Error loading textures\n");
		return (1);
	}
	return (0);
}

mlx_texture_t	*pick_tex(t_algorithmique *a, t_game *g)
{
	if (a->side == 0)
	{
		if (a->ray_dir_x > 0)
			return (g->tex_we);
		return (g->tex_ea);
	}
	if (a->ray_dir_y > 0)
		return (g->tex_no);
	return (g->tex_so);
}

void	pad_existing_line(char **map, int row, size_t max_len)
{
	size_t	len;
	char	*newp;

	len = 0;
	while (map[row][len])
		len++;
	if (len < max_len)
	{
		newp = realloc(map[row], max_len + 1);
		if (!newp)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}
		while (len < max_len)
		{
			newp[len] = '1';
			len++;
		}
		newp[max_len] = '\0';
		map[row] = newp;
	}
}

void	pad_null_line(char **map, int row, size_t max_len)
{
	size_t	len;
	char	*newp;

	newp = malloc(max_len + 1);
	if (!newp)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	len = 0;
	while (len < max_len)
	{
		newp[len] = '1';
		len++;
	}
	newp[max_len] = '\0';
	map[row] = newp;
}
