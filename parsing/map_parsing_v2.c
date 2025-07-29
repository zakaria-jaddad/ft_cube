/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:43:09 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/07/29 14:54:23 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	map_clean(t_depot *depot)
{
	int	i;

	i = 0;
	while (depot->map[i])
	{
		depot->map[i] = ft_strtrim(depot->map[i], "\n");
		if (!depot->map[i])
		{
			perror("malloc");
			ft_split_free(depot->map);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_not_pp(char c)
{
	if (c != 'N' && c != 'S'
		&& c != 'W' && c != 'E')
		return (1);
	return (0);
}
