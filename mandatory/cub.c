/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 06:38:26 by zajaddad          #+#    #+#             */
/*   Updated: 2025/12/10 17:06:27 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

// void f()
// {
// 	system("leaks cub3D");
// }
int	main(int ac, char **av)
{
	t_depot	depot;
	// atexit(f);

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
