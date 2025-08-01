/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_v2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:43:09 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/07/31 15:33:29 by ilarhrib         ###   ########.fr       */
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

int	three_elements_check(char **splitted_colors)
{
	int	i;
	
	i = 0;
	while (splitted_colors[i])
		i++;
	if (i != 3)
	{
		ft_fprintf(2, "Provide no more than 3 colors\n");
		return (1);
	}
	return (0);
}
