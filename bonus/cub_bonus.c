#include "includes/cube_bonus.h"
#include <stdlib.h>

int main(int ac, char **av) {
  t_depot depot;

  if (ac != 2)
  {
    write(2, "Please provide only the exec and map files\n", 44);
    printf("Rj3 t7awa\n");
    return (1);
  }
  if (depot_init(&depot))
    return (1);
  if (cub_parse(av[1], &depot))
  {
    printf("Rj3 t7awa\n");
    free_depot(&depot);
    return (1);
  }
  print_elements(&depot);
   if (cub_raycast(&depot)){
     return (1);
   }
  return (0);
}

int depot_init(t_depot *depot) {
  depot->floor_color_R = 0;
  depot->floor_color_G = 0;
  depot->floor_color_B = 0;
  depot->ceiling_color_R = 0;
  depot->ceiling_color_G = 0;
  depot->ceiling_color_B = 0;
  depot->path_to_NO = NULL;
  depot->path_to_SO = NULL;
  depot->path_to_WE = NULL;
  depot->path_to_EA = NULL;
  depot->map = NULL;
  depot->f_colors_flag = 0;
  depot->c_colors_flag = 0;
  depot->EA = 0;
  depot->NO = 0;
  depot->SO = 0;
  depot->WE = 0;
  return (0);
}
