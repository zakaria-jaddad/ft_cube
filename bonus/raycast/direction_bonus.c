/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:18:18 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/10 17:42:04 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_bonus.h"

double	get_direction_x(t_direction direction)
{
	if (direction == no)
		return (0);
	if (direction == so)
		return (0);
	if (direction == we)
		return (-1);
	else
		return (1);
}

double	get_direction_y(t_direction direction)
{
	if (direction == no)
		return (-1);
	if (direction == so)
		return (1);
	if (direction == we)
		return (0);
	else
		return (0);
}

t_direction	get_direction(t_depot *depot)
{
	if (depot->no == 1)
		return (no);
	if (depot->so == 1)
		return (so);
	if (depot->we == 1)
		return (we);
	else
		return (ea);
}
