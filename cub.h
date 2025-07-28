/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 01:59:51 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/07/28 04:00:16 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 7
# endif


typedef struct s_depot
{
	char	*map_file;
}	t_depot;

char	*read_and_stock(int fd, char *line);
char	*get_next_line(int fd);
char	*get_till_n_line(char *line);
char	*new_line_exe(char *line);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char *line, char *buff);

//----------------Parsing-------------------//
int	cub_parse(char *path, t_depot *depot);
int	path_check(char *path);
int	read_and_check(int fd, t_depot *depot);

# endif