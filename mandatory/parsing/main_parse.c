/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 02:06:23 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/08/02 08:59:55 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

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
	if (read_and_check(fd, depot))
		return (1);
	return (0);
}

int	read_and_check(int fd, t_depot *depot)
{
	char	*line;
	int		first_itr;

	first_itr = 1;
	while (1)
	{
		line = ft_gnl(fd);
		if (!line && first_itr == 1)
		{
			write(2, "empty file\n", 12);
			return (1);
		}
		else if (!line)
			break ;
		if (!*line || *line == '\n')
			continue;
		if (parse_line(line, depot))
		{
			free(line);
			return (1);
		}
		if (all_info_checked(depot))
		{
			if (clean_path(depot))
				return (1);
			free(line);
			break ;
		}
		first_itr++;
		free(line);
	}
	print_elements(depot);
	if (read_map(fd, depot))
		return (1);
	retreive_player_pos(depot);
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
	if (ft_strcmp(*str, "NO") == 0
		|| ft_strcmp(*str, "SO") == 0 || ft_strcmp(*str, "WE") == 0
		|| ft_strcmp(*str, "EA") == 0)
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
	if (ft_strcmp(str[0], "NO") == 0 && !depot->path_to_NO)
		depot->path_to_NO = ft_strdup(str[1]);
	else if (ft_strcmp(str[0], "SO") == 0 && !depot->path_to_SO)
		depot->path_to_SO = ft_strdup(str[1]);
	else if (ft_strcmp(str[0], "WE") == 0 && !depot->path_to_WE)
		depot->path_to_WE = ft_strdup(str[1]);
	else if (ft_strcmp(str[0], "EA") == 0 && !depot->path_to_EA)
		depot->path_to_EA = ft_strdup(str[1]);
	return (0);
}

int	color_check(char **str, t_depot *depot)
{
	if (!ft_strcmp(str[0], "F"))
	{
		printf("%s\n", str[1]);
		if (clean_and_add_floor(str[1], depot))
			return (1);
	}
	else if (!ft_strcmp(str[0], "C"))
	{
		
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
