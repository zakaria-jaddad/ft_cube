/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 06:38:26 by zajaddad          #+#    #+#             */
/*   Updated: 2025/11/10 09:56:54 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"
#include <stdio.h>
#include <unistd.h>

int	main(int ac, char **av)
{



  close(1);
  int out = printf("hello world");
  write(1, "hello world", 11);
  int alo = ft_fprintf(1, "hello world");

  fprintf(stderr, "%d\n", out);
  fprintf(stderr, "%d\n", alo);


    return 0;

	t_depot	depot;

	if (ac != 2)
		return (write(2, "Please provide only the exec and map files\n", 44),
			1);
	ft_bzero(&depot, sizeof(t_depot));
	if (cub_parse(av[1], &depot))
		return (free_depot(&depot), 1);
	if (cub_raycast(&depot))
		return (1);
	return (0);
}
