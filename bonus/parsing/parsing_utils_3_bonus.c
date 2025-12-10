/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:34:22 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/10 16:34:24 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_bonus.h"

int	assign_ceiling_color(char *color_str, int index, t_depot *depot)
{
	int	color_val;

	color_val = ft_atoi(color_str);
	if (!range_check(color_val))
	{
		ft_fprintf(2, "%s\n", "Invalid colors range");
		return (1);
	}
	if (index == 0)
		depot->ceiling_color_r = color_val;
	else if (index == 1)
		depot->ceiling_color_g = color_val;
	else if (index == 2)
		depot->ceiling_color_b = color_val;
	else
	{
		ft_fprintf(2, "%s\n", "More than 3 colors");
		return (1);
	}
	return (0);
}
