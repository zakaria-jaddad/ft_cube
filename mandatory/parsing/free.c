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

#include "../includes/parsing.h"

static char	**allocate_father(char **mother, int *count)
{
	int		i;
	char	**father;

	i = 0;
	while (mother[i])
		i++;
	*count = i;
	father = malloc((sizeof(char *) * (i + 2)));
	if (!father)
		perror("malloc");
	return (father);
}

char	**ft_realloc(char **mother, char *child)
{
	int		i;
	int		len;
	char	**father;

	father = allocate_father(mother, &len);
	if (!father)
		return (NULL);
	i = 0;
	while (i < len)
	{
		father[i] = mother[i];
		i++;
	}
	father[i] = ft_strdup(child);
	if (!father[i])
		return (perror("malloc"), free(father), NULL);
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
	ft_split_free(depot->map);
}

int	handle_identifiers(char **str, t_depot *depot)
{
	if (ft_strcmp(*str, "NO") == 0 || ft_strcmp(*str, "SO") == 0
		|| ft_strcmp(*str, "WE") == 0 || ft_strcmp(*str, "EA") == 0)
	{
		if (check_and_fill(str, depot))
			return (1);
	}
	else if (color_check(str, depot))
		return (1);
	return (0);
}
