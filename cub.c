/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 01:57:38 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/07/28 02:06:09 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
	return (0);
}
