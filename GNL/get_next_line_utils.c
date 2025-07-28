/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarhrib <ilarhrib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:13:04 by ilarhrib          #+#    #+#             */
/*   Updated: 2025/07/28 02:16:04 by ilarhrib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	ch = (char)c;
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)&s[i]);
		i++;
	}
	if (ch == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *line, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!line)
	{
		line = (char *)malloc(sizeof(char));
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	if (!buff)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(buff) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i] != '\0')
		str[i++] = line[j++];
	j = 0;
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[i] = '\0';
	return (free(line), str);
}
