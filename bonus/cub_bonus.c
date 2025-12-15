/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:48:00 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/10 17:48:03 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube_bonus.h"

int	main(int ac, char **av)
{
	t_depot	depot;

	if (ac != 2)
		return (write(2, "Please provide only the exec and map files\n", 44),
			1);
	ft_bzero(&depot, sizeof(t_depot));
	if (cub_parse(av[1], &depot))
	{
		close(depot.fd);
		return (free_depot(&depot), 1);
	}
	close(depot.fd);
	if (cub_raycast(&depot))
		return (free_depot(&depot), 1);
	free_depot(&depot);
	return (0);
}
