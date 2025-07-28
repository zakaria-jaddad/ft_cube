/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 02:06:23 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/07/28 08:50:23 by ilarhrib         ###   ########.fr       */
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

int	path_check(char *path)
{
	if (!path)
		return (0);
	while (*path)
		path++;
	if (*(path - 4) == '.' && *(path - 3) == 'c'
		&& *(path - 2) == 'u' && *(path - 1) == 'b')
		return (1);
	else
		write(2, "Invalid extension!\n", 21);
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
		if (parse_line(line, depot))
			return (1);
		first_itr++;
	}
	return (0);
}

int	parse_line(char *line, t_depot *depot)
{
	char	**str;

	str = ft_split(line, ' ');
	if (!str || !str[1] || !str[0])
	{
		write(2, "Parse error in path!\n", 22);
		return (1);
	}
	if (ft_strcmp(*str, "NO") == 0
		|| ft_strcmp(*str, "SO") == 0 || ft_strcmp(*str, "WE") == 0
		|| ft_strcmp(*str, "EA") == 0)
	{
		if (check_and_fill(str, depot))
			return (1);
	}
	else
		write(2, "Wrong Identifiers!\n", 20);
	ft_free(str);
	return (0);
}

int	check_and_fill(char **str, t_depot *depot)
{
	if (!path_check_v2(str[1]))
		return (1);
	if (ft_strcmp(*str, "NO") == 0 && !depot->path_to_NO)
		depot->path_to_NO = ft_strdup(str[1]);
	else if (ft_strcmp(*str, "SO") == 0 && !depot->path_to_SO)
		depot->path_to_SO = ft_strdup(str[1]);
	else if (ft_strcmp(*str, "WE") == 0 && !depot->path_to_WE)
		depot->path_to_WE = ft_strdup(str[1]);
	else if (ft_strcmp(*str, "EA") == 0 && !depot->path_to_EA)
		depot->path_to_EA = ft_strdup(str[1]);
	return (0);
}
