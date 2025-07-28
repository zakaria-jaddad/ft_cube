/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:32:50 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/07/28 07:51:51 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*d;

	d = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (d == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		d[i] = s1[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}
