/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:34:07 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/10 17:00:32 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_bonus.h"

void	pad_map_lines_n(char **map, int rows)
{
	size_t	max_len;
	int		i;

	if (!map || rows <= 0)
		return ;
	max_len = get_max_width(map, rows);
	i = 0;
	while (i < rows)
	{
		if (map[i])
			pad_one_line(&map[i], max_len);
		else
			create_new_line(&map[i], max_len);
		i++;
	}
}

void	pad_map_lines(char **map)
{
	int	rows;

	rows = 0;
	if (!map)
		return ;
	while (map[rows])
		rows++;
	pad_map_lines_n(map, rows);
}
