/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:34:07 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/15 15:08:37 by ilarhrib         ###   ########.fr       */
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

void	*ft_pad_realloc(void *ptr, size_t current_len, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		if (current_len < new_size)
			ft_memcpy(new_ptr, ptr, current_len);
		else
			ft_memcpy(new_ptr, ptr, new_size);
		free(ptr);
	}
	return (new_ptr);
}
