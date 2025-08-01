/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 01:57:38 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/08/01 06:57:52 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

int main(int ac, char **av) {
  if (ac != 2) {
    write(2, "Please provide only the exec and map files\n", 44);
    return (1);
  }
  t_depot depot;
  if (depot_init(&depot))
    return (1);
  if (cub_parse(av[1], &depot))
  {
    free_depot(&depot);
    return (1);
  }
    return (1);
  // if (cub_raycast(&depot))
  //   return (1);// sorry brother hh gadit parsing dyal map algo okda mn pc dyali so commentit lik hadchi
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
