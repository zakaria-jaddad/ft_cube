/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 01:57:38 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/07/28 08:45:00 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		write(2, "Please provide only the exec and map files\n", 44);
		return (1);
	}
	t_depot	depot;
	if (cub_parse(av[1], &depot))
		return (1);
	printf("NO --> %s\n", depot.path_to_NO);
	printf("SO --> %s\n", depot.path_to_SO);
	printf("WE --> %s\n", depot.path_to_WE);
	printf("EA --> %s\n", depot.path_to_EA);
	return (0);
}
