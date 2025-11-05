/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:18:18 by zajaddad          #+#    #+#             */
/*   Updated: 2025/08/06 16:19:07 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_bonus.h"

double	get_direction_x(t_direction direction)
{
	if (direction == NO)
		return (0);
	if (direction == SO)
		return (0);
	if (direction == WE)
		return (-1);
	else
		return (1);
}

double	get_direction_y(t_direction direction)
{
	if (direction == NO)
		return (-1);
	if (direction == SO)
		return (1);
	if (direction == WE)
		return (0);
	else
		return (0);
}

t_direction	get_direction(t_depot *depot)
{
	if (depot->NO == 1)
		return (NO);
	if (depot->SO == 1)
		return (SO);
	if (depot->WE == 1)
		return (WE);
	else
		return (EA);
}
