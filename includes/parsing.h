/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 08:41:59 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/07/28 08:44:25 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef struct s_depot
{
	char	**map;
	char	*path_to_NO;
	char	*path_to_SO;
	char	*path_to_WE;
	char	*path_to_EA;

}	t_depot;

//----------------Cleaners------------------//
void	ft_free(char **str);

//----------------Parsing-------------------//
int	cub_parse(char *path, t_depot *depot);
int	path_check(char *path);
int	read_and_check(int fd, t_depot *depot);
int	path_check_v2(char *path);
int	parse_line(char *line, t_depot *depot);
int	check_and_fill(char **str, t_depot *depot);

#endif