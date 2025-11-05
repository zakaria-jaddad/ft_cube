#include "../includes/cube.h"

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

int	load_textures(t_game *g, char *no, char *so, char *we, char *ea)
{
	printf("%s\n%s\n%s\n%s\n", no, so, we, ea);
	if (access(no, F_OK) != 0)
		printf("2000\n");
	else
		printf("Found %s\n", no);
	g->tex_no = mlx_load_png(no);
	g->tex_so = mlx_load_png(so);
	g->tex_we = mlx_load_png(we);
	g->tex_ea = mlx_load_png(ea);
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
