/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 08:41:59 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/11/10 09:52:18 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../../lib/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_parse	t_parse;

typedef struct s_depot
{
	char				**map;
	char				*path_to_no;
	char				*path_to_so;
	char				*path_to_we;
	char				*path_to_ea;
	int					floor_color_r;
	int					floor_color_g;
	int					floor_color_b;
	int					ceiling_color_r;
	int					ceiling_color_g;
	int					ceiling_color_b;
	unsigned int		f_color;
	unsigned int		c_color;
	int					c_colors_flag;
	int					f_colors_flag;
	int					NO;
	int					SO;
	int					WE;
	int					EA;
	double				player_x;
	double				player_y;

}						t_depot;

//----------------Utils------------------//
char					**ft_realloc(char **mother, char *child);
int						is_number(char *str);
int						range_check(int color);
void					print_elements(t_depot *depot);
void					free_depot(t_depot *depot);
int						three_elements_check(char **split_colors);
uint32_t				rgb_convert(int r, int g, int b);
uint32_t				rgba_convert(int r, int g, int b, int a);
int						process_line(char *line, t_depot *depot);
int						process_split_colors(char **split_colors,
							t_depot *depot);
int						process_split_ceiling(char **split_colors,
							t_depot *depot);
int						assign_floor_color(t_depot *depot, int color,
							int index);
int						assign_ceiling_color(t_depot *depot, int color,
							int index);
int						check_horizontal_walls(char **map, int last_row_idx);
int						check_vertical_walls(char **map);

//----------------Parsing-------------------//
int						cub_parse(char *path, t_depot *depot);
int						path_check(char *path);
int						read_and_check(int fd, t_depot *depot);
int						path_check_v2(char *path);
int						parse_line(char *line, t_depot *depot);
int						check_and_fill(char **str, t_depot *depot);
int						color_check(char **str, t_depot *depot);
int						clean_and_add_floor(char *str, t_depot *depot);
int						convert_and_add_floor(char **str, t_depot *depot);
int						convert_and_add_ceiling(char **str, t_depot *depot);
int						clean_and_add_ceiling(char *str, t_depot *depot);
int						depot_init(t_depot *depot);
int						read_map(int fd, t_depot *depot);
int						all_info_checked(t_depot *depot);
int						is_color(char **str);
int						map_parse(t_depot *depot);
int						player_point_parsing(t_depot *depot);
int						advanced_map_parsing(t_depot *depot);
int						map_clean(t_depot *depot);
int						is_not_pp(char c);
int						ultra_parsing(t_depot *depot);
int						colors_parse(char **str);
int						ultra_map_parse(t_depot *depot);
int						all_ones(char *str);
int						is_closed_by_walls(char **map);
int						not_player_point(char c);
int						retrieve_player_pos(t_depot *depot);
int						clean_path(t_depot *depot);
void					pad_map_lines_n(char **map, int rows);
void					pad_map_lines(char **map);
int						player_point_count(t_depot *depot, int j);
size_t					get_max_len(char **map, int rows);
void					pad_existing_line(char **map, int row, size_t max_len);
void					pad_null_line(char **map, int row, size_t max_len);

#endif