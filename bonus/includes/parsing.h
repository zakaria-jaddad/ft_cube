/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 08:41:59 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/10/31 10:07:50 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H
#include "../libft/libft.h"
#include <fcntl.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_parse t_parse;

typedef struct s_depot {
  char **map;
  char *path_to_NO;
  char *path_to_SO;
  char *path_to_WE;
  char *path_to_EA;
  int floor_color_R;
  int floor_color_G;
  int floor_color_B;
  int ceiling_color_R;
  int ceiling_color_G;
  int ceiling_color_B;
  unsigned int f_color; // ara chi bouayssa
  unsigned int c_color; // ara chi bouayssa
  int c_colors_flag;
  int f_colors_flag;
  int NO;
  int SO;
  int WE;
  int EA;
  double player_x;
  double player_y;

} t_depot;

//----------------Utils------------------//
char **ft_realloc(char **mother, char *child);
int is_number(char *str);
int range_check(int color);
void print_elements(t_depot *depot);
void free_depot(t_depot *depot);
int three_elements_check(char **splitted_colors);
uint32_t rgb_convert(int r, int g, int b);
uint32_t rgba_convert(int r, int g, int b, int a);

//----------------Parsing-------------------//
int cub_parse(char *path, t_depot *depot);
int path_check(char *path);
int read_and_check(int fd, t_depot *depot);
int path_check_v2(char *path);
int parse_line(char *line, t_depot *depot);
int check_and_fill(char **str, t_depot *depot);
int color_check(char **str, t_depot *depot);
int clean_and_add_floor(char *str, t_depot *depot);
int convert_and_add_floor(char **str, t_depot *depot);
int convert_and_add_ceiling(char **str, t_depot *depot);
int clean_and_add_ceiling(char *str, t_depot *depot);
int depot_init(t_depot *depot);
int read_map(int fd, t_depot *depot);
int all_info_checked(t_depot *depot);
int is_color(char **str);
int is_map(char *str, t_depot *depot);
int map_parse(t_depot *depot);
int player_point_parsing(t_depot *depot);
int advanced_map_parsing(t_depot *depot);
int map_clean(t_depot *depot);
int is_not_pp(char c);
int ultra_parsing(t_depot *depot);
int colors_parse(char **str);
int ultra_map_parse(t_depot *depot);
int all_ones(char *str);
int is_closed_by_walls(char **map);
int not_player_point(char c);
int retreive_player_pos(t_depot *depot);
int clean_path(t_depot *depot);
void pad_map_lines_n(char **map, int rows);
void pad_map_lines(char **map);
int doors_parsing(char **map);

#endif
