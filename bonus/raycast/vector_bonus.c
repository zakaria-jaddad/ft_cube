/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:22:25 by zajaddad          #+#    #+#             */
/*   Updated: 2025/08/06 16:35:41 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_bonus.h"

t_vector	*create_vector(double x, double y)
{
	t_vector	*v;

	v = malloc(sizeof(t_vector));
	if (v == NULL)
		return (NULL);
	v->x = x;
	v->y = y;
	return (v);
}
