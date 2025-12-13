/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigrav <antigrav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:00:00 by antigrav          #+#    #+#             */
/*   Updated: 2025/12/10 16:59:26 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (!ft_isdigit(str[i]) && str[i] != ',' && str[i] != '\n')
			return (ft_fprintf(2, "Colors should be digits\n"), 1);
		i++;
	}
	return (0);
}

int	range_check(int color)
{
	if (color <= 255 && color >= 0)
		return (1);
	return (0);
}

int	process_line(char *line, t_depot *depot)
{
	if (!line || *line == '\n')
		return (0);
	if (parse_line(line, depot))
		return (1);
	if (all_info_checked(depot))
	{
		if (clean_path(depot))
			return (1);
		return (2);
	}
	return (0);
}

uint32_t	rgb_convert(int r, int g, int b)
{
	return (((uint32_t)(r & 0xFF) << 24) | ((uint32_t)(g & 0xFF) << 16)
		| ((uint32_t)(b & 0xFF) << 8) | 0xFFu);
}

int	column_check(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
	{
		write(2, "Invalid color format!\n", 23);
		return (1);
	}
	return (0);
}
