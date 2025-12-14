/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:20:46 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/10 17:42:27 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_bonus.h"

void	free_player(t_player *player)
{
	if (player == NULL)
		return ;
	free(player->plane);
	free(player->direction);
	free(player);
}

static t_player	*create_player(void)
{
	t_player	*p;

	p = malloc(sizeof(t_player));
	if (p == NULL)
		return (NULL);
	ft_bzero(p, sizeof(t_player));
	return (p);
}

static void	set_player_cor(double *x, double *y, t_depot *depot)
{
	*x = depot->player_x + 0.5;
	*y = depot->player_y + 0.5;
}

static void	init_plane(double *px, double *py, double dx, double dy)
{
	if (dx == 0 && dy == -1)
	{
		*px = 0.66;
		*py = 0;
	}
	else if (dx == 0 && dy == 1)
	{
		*px = -0.66;
		*py = 0;
	}
	else if (dx == 1 && dy == 0)
	{
		*px = 0;
		*py = 0.66;
	}
	else if (dx == -1 && dy == 0)
	{
		*px = 0;
		*py = -0.66;
	}
	else
	{
		*px = 0;
		*py = 0;
	}
}

t_player	*init_player(t_depot *depot)
{
	t_direction	d;
	t_player	*p;

	d = get_direction(depot);
	p = create_player();
	if (p == NULL)
		return (NULL);
	p->direction = create_vector(get_direction_x(d), get_direction_y(d));
	if (p->direction == NULL)
		return (free_player(p), NULL);
	set_player_cor(&p->map_x, &p->map_y, depot);
	p->plane = create_vector(0, 0);
	if (p->plane == NULL)
		return (free_player(p), NULL);
	init_plane(&p->plane->x, &p->plane->y, p->direction->x, p->direction->y);
	p->bobbing_val = 10;
	p->bob_offset = BOB_AMPLITUDE;
	return (p);
}
