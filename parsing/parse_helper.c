/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 07:46:49 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/07/28 08:52:17 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int	path_check_v2(char *path)
{
	printf("%s\n", path);
	
	if (!path)
		return (0);
	while (*path)
		path++;
	printf("%c\n", path[5]);
	if (*(path - 4) == '.' && *(path - 3) == 'p'
		&& *(path - 2) == 'n' && *(path - 1) == 'g')
		return (1);
	else
		write(2, "Invalid extension!\n", 20);
	return (0);
}
