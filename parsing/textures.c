#include"../includes/cube.h"

void destroy_textures(t_game *g)
{
    if (g->tex_no)
		mlx_delete_texture(g->tex_no);
    if (g->tex_so)
		mlx_delete_texture(g->tex_so);
    if (g->tex_we)
		mlx_delete_texture(g->tex_we);
    if (g->tex_ea)
		mlx_delete_texture(g->tex_ea);
    g->tex_no = 0;
	g->tex_so = 0;
	g->tex_we = 0;
	g->tex_ea = 0;
}

int load_textures(t_game *g, char *no, char *so, char *we, char *ea)
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
      return 1;
    }
    return 0;
}

mlx_texture_t *pick_tex(const t_algorithmique *a, const t_game *g)
{
    if (a->side == 0)
    {
        if (a->ray_dir_x > 0)
			return g->tex_we;
        return g->tex_ea;
    }
    if (a->ray_dir_y > 0)
		return g->tex_no;
    return g->tex_so;
}

// RGBA bytes -> pack to ARGB to match your 0xFF202020 usage.
uint32_t    get_tex_pixel(mlx_texture_t *tex, int x, int y)
{
    uint8_t *p;
    int     bpp;

    if (!tex)
        return 0xFFFF00FF; // debug magenta (ARGB)
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x >= (int)tex->width)  x = (int)tex->width - 1;
    if (y >= (int)tex->height) y = (int)tex->height - 1;

    bpp = (int)tex->bytes_per_pixel;               // should be 4 (RGBA)
    p = tex->pixels + (y * (int)tex->width + x) * bpp;

    // PNG is RGBA; your mlx_put_pixel seems to expect ARGB (since 0xFF202020 looks gray).
    // Convert RGBA -> ARGB:
    return ((uint32_t)p[3] << 24) | ((uint32_t)p[0] << 16)
         | ((uint32_t)p[1] << 8)  | (uint32_t)p[2];
}
