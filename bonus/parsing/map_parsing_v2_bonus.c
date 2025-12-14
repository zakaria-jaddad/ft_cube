/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_v2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:43:09 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/11/10 10:54:03 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_bonus.h"

int	map_clean(t_depot *depot)
{
	int		i;
	char	*tmp;

	i = 0;
	while (depot->map[i])
	{
		tmp = ft_strtrim(depot->map[i], "\n");
		if (!tmp)
		{
			perror("malloc");
			return (1);
		}
		free(depot->map[i]);
		depot->map[i] = tmp;
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

int	colors_parse(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i != 3)
	{
		ft_fprintf(2, "More than three colors!\n");
		return (1);
	}
	return (0);
}

int	all_ones(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ' && str[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}
