/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 07:53:56 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/08/02 09:03:57 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_bonus.h"

static void	copy_pointers(char **dest, char **src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
}

char	**ft_realloc(char **mother, char *child)
{
	int		i;
	char	**father;

	i = 0;
	while (mother[i])
		i++;
	father = malloc(sizeof(char *) * (i + 2));
	if (!father)
		return (perror("malloc"), NULL);
	copy_pointers(father, mother);
	father[i] = ft_strdup(child);
	if (!father[i])
	{
		perror("malloc");
		return (free(father), NULL);
	}
	father[i + 1] = NULL;
	free(mother);
	return (father);
}

void	free_depot(t_depot *depot)
{
	free(depot->path_to_no);
	free(depot->path_to_ea);
	free(depot->path_to_we);
	free(depot->path_to_so);
	free(depot->path_to_door);
	ft_split_free(depot->map);
}
