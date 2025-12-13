/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 02:06:23 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/11/05 02:02:45 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_bonus.h"

int	cub_parse(char *path, t_depot *depot)
{
	int	fd;

	if (!path_check(path))
		return (1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		write(2, "File Invalid!\n", 15);
		return (1);
	}
	depot->fd = fd;
	if (read_and_check(fd, depot))
		return (1);
	return (0);
}

int	read_and_check(int fd, t_depot *depot)
{
	char	*line;
	int		status;

	while (1)
	{
		line = ft_gnl(fd);
		if (!line)
			break ;
		status = process_line(line, depot);
		free(line);
		if (status == 1)
			return (1);
		if (status == 2)
			break ;
	}
	if (read_map(fd, depot))
		return (1);
	retrieve_player_pos(depot);
	return (0);
}

int	parse_line(char *line, t_depot *depot)
{
	char	**str;

	str = ft_split(ft_strtrim(line, "\t\r"), ' ');
	if (!str)
	{
		perror("malloc");
		return (1);
	}
	if (ft_strcmp(*str, "NO") == 0 || ft_strcmp(*str, "SO") == 0
		|| ft_strcmp(*str, "WE") == 0 || ft_strcmp(*str, "EA") == 0
		|| ft_strcmp(*str, "DR") == 0)
	{
		if (check_and_fill(str, depot))
		{
			ft_split_free(str);
			return (1);
		}
	}
	else if (color_check(str, depot))
	{
		ft_split_free(str);
		return (1);
	}
	ft_split_free(str);
	return (0);
}

int	check_and_fill(char **str, t_depot *depot)
{
	if (!path_check_v2(str[1]))
		return (1);
	if (ft_strcmp(str[0], "NO") == 0 && !depot->path_to_no)
		depot->path_to_no = ft_strdup(str[1]);
	else if (ft_strcmp(str[0], "SO") == 0 && !depot->path_to_so)
		depot->path_to_so = ft_strdup(str[1]);
	else if (ft_strcmp(str[0], "WE") == 0 && !depot->path_to_we)
		depot->path_to_we = ft_strdup(str[1]);
	else if (ft_strcmp(str[0], "EA") == 0 && !depot->path_to_ea)
		depot->path_to_ea = ft_strdup(str[1]);
	else if (ft_strcmp(str[0], "DR") == 0 && !depot->path_to_door)
		depot->path_to_door = ft_strdup(str[1]);
	return (0);
}

int	color_check(char **str, t_depot *depot)
{
	if (!ft_strcmp(str[0], "F"))
	{
		if (column_check(str[1]))
			return (1);
		if (clean_and_add_floor(str[1], depot))
			return (1);
	}
	else if (!ft_strcmp(str[0], "C"))
	{
		if (column_check(str[1]))
			return (1);
		if (clean_and_add_ceiling(str[1], depot))
			return (1);
	}
	else
	{
		write(2, "Wrong Identifiers!\n", 20);
		return (1);
	}
	return (0);
}
