#include "includes/cube_bonus.h"

int main(int ac, char **av) {
	t_depot depot;

	if (ac != 2)
	{
		write(2, "Please provide only the exec and map files\n", 44);
		return (1);
	}
	if (depot_init(&depot))
		return (1);
	if (cub_parse(av[1], &depot))
	{
		free_depot(&depot);
		return (1);
	}
	 if (cub_raycast(&depot)){
		 return (1);
	 }
	return (0);
}

int depot_init(t_depot *depot) {
	depot->floor_color_r = 0;
	depot->floor_color_g = 0;
	depot->floor_color_b = 0;
	depot->ceiling_color_r = 0;
	depot->ceiling_color_g = 0;
	depot->ceiling_color_b = 0;
	depot->path_to_no = NULL;
	depot->path_to_so = NULL;
	depot->path_to_we = NULL;
	depot->path_to_ea = NULL;
	depot->path_to_door = NULL;
	depot->map = NULL;
	depot->f_colors_flag = 0;
	depot->c_colors_flag = 0;
	depot->EA = 0;
	depot->NO = 0;
	depot->SO = 0;
	depot->WE = 0;
	return (0);
}
