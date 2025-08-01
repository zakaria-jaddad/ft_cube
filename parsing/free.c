/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 07:53:56 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/07/31 14:43:52 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

char	**ft_realloc(char **mother, char *child)
{
	int		i;
	char	**father;

	i = 0;
	while (mother[i])
		i++;
	father = malloc((sizeof(char *) * (i + 2)));
	if (!father)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	while (mother[i])
	{
		father[i] = mother[i];
		i++;
	}
	father[i] = ft_strdup(child);
	if (!father[i])
	{
		perror("malloc");
		return (NULL);
	}
	i++;
	father[i] = NULL;
	free(mother);
	mother = NULL;
	return (father);
}

void	print_elements(t_depot *depot)
{
	int		i;
	int		j;
	char	**map;

	map = depot->map;
	i = 0;
	j = 0;
	printf("NO --> %s\n", depot->path_to_NO);
	printf("SO --> %s\n", depot->path_to_SO);
	printf("WE --> %s\n", depot->path_to_WE);
	printf("EA --> %s\n", depot->path_to_EA);
	printf("FLOOR_RED --> %d\n", depot->floor_color_R);
	printf("FLOOR_GREEN --> %d\n", depot->floor_color_G);
	printf("FLOOR_BLUE --> %d\n", depot->floor_color_B);
	printf("CEILING_RED --> %d\n", depot->ceiling_color_R);
	printf("CEILING_GREEN --> %d\n", depot->ceiling_color_G);
	printf("CEILING_BLUE --> %d\n", depot->ceiling_color_B);
}

void	free_depot(t_depot *depot)
{
		ft_split_free(depot->map);
		free(depot->path_to_EA);
		free(depot->path_to_NO);
		free(depot->path_to_WE);
		free(depot->path_to_SO);
}
