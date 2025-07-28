/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 02:06:23 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/07/28 05:26:46 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	cub_parse(char *path, t_depot *depot)
{
	int	fd;

	if (path_check(path))
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
	while (*path)
		path++;
	if (*(path - 4) != '.' && *(path - 3) != 'c'
		&& *(path - 2) != 'u' && *(path - 1) != 'b')
		{
			write(2, "Invalid extension!\n", 20);
			return (1);
		}
	return (0);
}

int	read_and_check(int fd, t_depot *depot)
{
	char	*line;
	int		first_itr;

	first_itr = 1;
	while (line)
	{
		line = get_next_line(fd);
		if (!line && first_itr == 1)
		{
			write(2, "empty file\n", 12);
			return (1);
		}
		else if (!line)
			break ;
		//if (parse_line(line, depot))
		//	return (1);
		first_itr++;
	}
	return (0);
}

//int	parse_line(char *line, t_depot *depot)
//{
//	char **str;

//	str = ft_split()
//}
