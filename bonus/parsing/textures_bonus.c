/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 01:59:52 by zajaddad          #+#    #+#             */
/*   Updated: 2025/11/05 06:51:20 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube_bonus.h"

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
	if (g->tex_dr)
		mlx_delete_texture(g->tex_dr);
	g->tex_no = NULL;
	g->tex_so = NULL;
	g->tex_we = NULL;
	g->tex_ea = NULL;
	g->tex_dr = NULL;
}

int	load_textures(t_game *g, t_depot *depot)
{
	g->tex_no = mlx_load_png(depot->path_to_no);
	g->tex_so = mlx_load_png(depot->path_to_so);
	g->tex_we = mlx_load_png(depot->path_to_we);
	g->tex_ea = mlx_load_png(depot->path_to_ea);
	g->tex_dr = mlx_load_png(depot->path_to_door);
	if (!g->tex_no || !g->tex_so || !g->tex_we || !g->tex_ea || !g->tex_dr)
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

int	trim_and_replace(char **path)
{
	char	*tmp;

	tmp = ft_strtrim(*path, "\n\t\r");
	if (!tmp)
		return (1);
	free(*path);
	*path = tmp;
	return (0);
}
